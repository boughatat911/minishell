#include "parser.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	if (c == '<')
		return (T_REDIR_IN);
	if (c == '>')
		return (T_REDIR_OUT);
	if (c == '\'')
		return (T_SQUOTE);
	if (c == '"')
		return (T_DQUOTE);
	if (c == '$')
		return (T_DOLLAR);
	if (is_space(c))
		return (T_WHITESPACE);
	return (T_WORD);
}

static char	*extract_word(char **input)
{
	char	*start;
	char	*word;
	int		len;

	start = *input;
	len = 0;
	while (start[len] && !is_space(start[len]) && !is_operator(start[len]))
		len++;
	word = ft_strndup(start, len);
	*input = start + len;
	return (word);
}

static char	*extract_quoted(char **input, char quote)
{
	char	*start;
	char	*end;
	char	*word;

	start = *input + 1;
	end = start;
	while (*end && *end != quote)
		end++;
	if (!*end)
		return (NULL);
	word = ft_strndup(start, end - start);
	*input = end + 1;
	return (word);
}

static t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static t_token	*add_token(t_token **tokens, t_token *new)
{
	t_token	*current;

	if (!*tokens)
		*tokens = new;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

static void	handle_redir(t_token **tokens, char **input)
{
	t_token	*token;

	if (**input == '>' && *(*input + 1) == '>')
	{
		token = create_token(T_REDIR_APPEND, ft_strdup(">>"));
		*input += 2;
	}
	else
	{
		token = create_token(get_token_type(**input), ft_strndup(*input, 1));
		(*input)++;
	}
	add_token(tokens, token);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	t_token	*token;
	char	*word;

	tokens = NULL;
	while (*input)
	{
		if (is_space(*input))
		{
			input++;
			continue;
		}
		if (is_operator(*input))
		{
			handle_redir(&tokens, &input);
			continue;
		}
		if (is_quote(*input))
		{
			word = extract_quoted(&input, *input);
			if (!word)
				break;
			token = create_token(get_token_type(*(input - 1)), word);
		}
		else
		{
			word = extract_word(&input);
			token = create_token(T_WORD, word);
		}
		if (!token)
			break;
		add_token(&tokens, token);
	}
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
} 