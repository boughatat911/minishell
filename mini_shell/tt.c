#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef enum e_token_type {
    STRING,
    WORD,
    PIPE,
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND,     // >>
    HEREDOC     // <<
} t_token_type;

typedef struct s_token {
    char *content;
    t_token_type type;
    int index;
    int ind;
    struct s_token *next;
} t_token;

t_token *new_token(char *content, t_token_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->content = content;
    tok->type = type;
    tok->next = (NULL);
    return (tok);
}

void add_token(t_token **lst, char *content, t_token_type type, int index)
{
    t_token *tok = new_token(content, type);
    if (!*lst)
        *lst = tok;
    else
	{
        t_token *tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = tok;
    }
		tok->index = index;
} 

char *substr(char *s, int start, int len)
{
    char *out = malloc(len + 1);
    if (!out)
        return (NULL);
    strncpy(out, s + start, len);
    out[len] = 0;
    return (out);
}
void qoute(t_token **tokens, int *i, char *input, int *index)
{
	int start;
	char quote;

	start = 0;
	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	add_token(tokens, substr(input, start, *i - start), STRING, *index);
	if (input[*i] == quote)
		(*i)++;
		(*index)++;
}
void	ft_word(t_token **tokens, int *i, char *input, int *index)
{
	int	start;
	start = *i;
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '|' &&
			input[(*i)] != '<' && input[(*i)] != '>' &&
			input[(*i)] != '"' && input[(*i)] != '\'')
		(*i)++;
	add_token(tokens, substr(input, start, (*i) - start), WORD, (*index));
	(*index)++;
}
void lexer(char *input, t_token **tokens)
{
    int i;
	int index;
	int start;
	i = 0;
	index = 1;
	while (input[i] == ' ') // skip space
		i++;
	if (input[i] == '|') // check | is first this is syntax error
	{
		printf("syntax error pipe\n");
		exit (1);
	}
	while (input[i])
	{

		if (input[i] == ' ')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, strdup(">>"), APPEND, index);
			i += 2;
			index++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(tokens, strdup("<<"), HEREDOC, index);
			i += 2;
			index++;
		}
		else if (input[i] == '>')
		{
			add_token(tokens, strdup(">"), REDIR_OUT, index);
			i++;
			index++;
		}
		else if (input[i] == '<')
		{
			add_token(tokens, strdup("<"), REDIR_IN, index);
			i++;
			index++;
		}
		else if (input[i] == '|')
		{
			if (input[i + 1 ] == '|')
			{
				printf("syntax error pipe\n");
				exit (1);
			}
			add_token(tokens, strdup("|"), PIPE, index);
			i++;
			index++;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			qoute(tokens, &i, input, &index);
			// char quote = input[i++];
			// start = i;
			// while (input[i] && input[i] != quote)
			// 	i++;
			// add_token(tokens, substr(input, start, i - start), STRING, index);
			// if (input[i] == quote)
			// 	i++;
			// index++;
		}
		else
		{
			ft_word(tokens, &i, input, &index);
			// start = i;
			// while (input[i] && input[i] != ' ' && input[i] != '|' &&
			// 		input[i] != '<' && input[i] != '>' &&
			// 		input[i] != '"' && input[i] != '\'')
			// 	i++;
			// add_token(tokens, substr(input, start, i - start), WORD, index);
			// index++;
		}
	}
}


int main()
{
    char *input = readline("minishell> ");
    t_token *tokens = NULL;
    t_token *copy = NULL;

    lexer(input, &tokens);
	copy = tokens;
    // print_tokens(tokens);
    while (tokens)
    {
        printf("Token: {%s} ==>  Type: %d, index ==> [%d]\n", tokens->content, tokens->type, tokens->index);
        tokens = tokens->next;
    }
// echo 'hello "yool"' | grep hello > file.txt | ls
	printf ("\n---------------------\n");
	while (copy)
    {
        printf("Token: %s\n", copy->content);
        copy = copy->next;
    }
	// int i = 0;
	// char **cmds = ft_split_pipe(input, '|');
	// int i = 0;

	// while (cmds[i])
	// {
	// 	printf("Command %d: [%s]\n", i, cmds[i]);
	// 	i++;
	// }
    return 0;
}
