// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>

// typedef enum e_token_type {
// 	WORD,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	APPEND,
// 	HEREDOC
// } t_token_type;

// typedef struct s_token {
// 	char *content;
// 	t_token_type type;
// 	struct s_token *next;
// } t_token;

// typedef struct s_redirect {
// 	int type;
// 	char *file;
// 	struct s_redirect *next;
// } t_redirect;

// typedef struct s_command {
// 	char **args;
// 	t_redirect *redirects;
// 	struct s_command *next;
// } t_command;

// // ---------- Token Utils ----------

// t_token *new_token(char *content, t_token_type type) {
// 	t_token *tok = malloc(sizeof(t_token));
// 	tok->content = content;
// 	tok->type = type;
// 	tok->next = NULL;
// 	return tok;
// }

// void add_token(t_token **lst, char *content, t_token_type type) {
// 	t_token *tok = new_token(content, type);
// 	if (!*lst)
// 		*lst = tok;
// 	else {
// 		t_token *tmp = *lst;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = tok;
// 	}
// }

// char *substr(char *s, int start, int len) {
// 	char *out = malloc(len + 1);
// 	strncpy(out, s + start, len);
// 	out[len] = 0;
// 	return out;
// }

// // ---------- Lexer ----------

// void lexer(char *input, t_token **tokens) {
// 	int i = 0, start;
// 	while (input[i] == '\t') i++;
// 	if (input[i] == '|') {
// 		printf("syntax error near pipe\n");
// 		exit(1);
// 	}

// 	while (input[i]) {
// 		if (input[i] == '\t')
// 			i++;
// 		else if (input[i] == '>' && input[i + 1] == '>') {
// 			add_token(tokens, strdup(">>"), APPEND);
// 			i += 2;
// 		} else if (input[i] == '<' && input[i + 1] == '<') {
// 			add_token(tokens, strdup("<<"), HEREDOC);
// 			i += 2;
// 		} else if (input[i] == '>') {
// 			add_token(tokens, strdup(">"), REDIR_OUT);
// 			i++;
// 		} else if (input[i] == '<') {
// 			add_token(tokens, strdup("<"), REDIR_IN);
// 			i++;
// 		} else if (input[i] == '|') {
// 			add_token(tokens, strdup("|"), PIPE);
// 			i++;
// 		} else if (input[i] == '"' || input[i] == '\'') {
// 			char quote = input[i++];
// 			start = i;
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			add_token(tokens, substr(input, start, i - start), WORD);
// 			if (input[i] == quote) i++;
// 		} else {
// 			start = i;
// 			while (input[i] && input[i] != '\t' && input[i] != '|' &&
// 					input[i] != '<' && input[i] != '>' &&
// 					input[i] != '"' && input[i] != '\'')
// 				i++;
// 			add_token(tokens, substr(input, start, i - start), WORD);
// 		}
// 	}
// }

// // ---------- Parser ----------

// t_command *parse_tokens(t_token *tokens) {
// 	t_command *cmd_head = NULL, *current = NULL;

// 	while (tokens) {
// 		t_command *new_cmd = malloc(sizeof(t_command));
// 		new_cmd->args = malloc(sizeof(char *) * 256);
// 		new_cmd->redirects = NULL;
// 		new_cmd->next = NULL;

// 		int i = 0;
// 		while (tokens && tokens->type != PIPE) {
// 			if (tokens->type == WORD) {
// 				new_cmd->args[i++] = strdup(tokens->content);
// 			} else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND || tokens->type == HEREDOC) {
// 				t_redirect *redir = malloc(sizeof(t_redirect));
// 				redir->type = tokens->type;
// 				tokens = tokens->next;
// 				redir->file = tokens && tokens->type == WORD ? strdup(tokens->content) : NULL;
// 				redir->next = new_cmd->redirects;
// 				new_cmd->redirects = redir;
// 			}
// 			tokens = tokens->next;
// 		}
// 		new_cmd->args[i] = NULL;

// 		if (!cmd_head)
// 			cmd_head = new_cmd;
// 		else
// 			current->next = new_cmd;
// 		current = new_cmd;

// 		if (tokens && tokens->type == PIPE)
// 			tokens = tokens->next;
// 	}
// 	return cmd_head;
// }

// // ---------- Debug Print ----------

// void print_tokens(t_token *tokens) {
// 	while (tokens) {
// 		printf("Token:\t%-10s\t|\tType:\t%d\n", tokens->content, tokens->type);
// 		tokens = tokens->next;
// 	}
// }

// void print_commands(t_command *cmds) {
// 	int i = 0;
// 	while (cmds) {
// 		printf("Command\t%d:\n", i++);
// 		int j = 0;
// 		while (cmds->args && cmds->args[j]) {
// 			printf("\tArg:\t%s\n", cmds->args[j]);
// 			j++;
// 		}
// 		t_redirect *redir = cmds->redirects;
// 		while (redir) {
// 			printf("\tRedirect:\tType\t%d\t->\t%s\n", redir->type, redir->file);
// 			redir = redir->next;
// 		}
// 		cmds = cmds->next;
// 	}
// }

// // ---------- Main ----------

// int main() {
// 	char *input = readline("minishell> ");
// 	// replace spaces with tabs for test purposes
// 	for (int i = 0; input[i]; i++)
// 		if (input[i] == ' ')
// 			input[i] = '\t';

// 	t_token *tokens = NULL;
// 	lexer(input, &tokens);

// 	printf("=== TOKENS ===\n");
// 	print_tokens(tokens);

// 	printf("\n=== PARSED COMMANDS ===\n");
// 	t_command *cmds = parse_tokens(tokens);
// 	print_commands(cmds);

// 	return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef enum e_token_type {
	WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC
} t_token_type;

typedef struct s_token {
	char			*content;
	t_token_type	type;
	struct s_token	*next;
} t_token;

typedef struct s_redirect {
	int					type;
	char				*file;
	struct s_redirect	*next;
} t_redirect;

typedef struct s_command {
	char				**args;
	t_redirect			*redirects;
	struct s_command	*next;
} t_command;

// ---------- Token Utils ----------

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->content = content;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **lst, char *content, t_token_type type)
{
	t_token	*tok;
	t_token	*tmp;

	tok = new_token(content, type);
	if (!*lst)
		*lst = tok;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
	}
}

char	*substr(char *s, int start, int len)
{
	char	*out;
	int		i;

	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

// ---------- Lexer ----------

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == '\t');
}

void	handle_quote(char *input, int *i, t_token **tokens)
{
	int		start;
	char	quote;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	add_token(tokens, substr(input, start, *i - start), WORD);
	if (input[*i] == quote)
		(*i)++;
}

void	lexer(char *input, t_token **tokens)
{
	int	i;
	int	start;

	i = 0;
	while (input[i] == '\t')
		i++;
	if (input[i] == '|')
	{
		printf("syntax error near pipe\n");
		exit(1);
	}
	while (input[i])
	{
		if (input[i] == '\t')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
			add_token(tokens, strdup(">>"), APPEND), i += 2;
		else if (input[i] == '<' && input[i + 1] == '<')
			add_token(tokens, strdup("<<"), HEREDOC), i += 2;
		else if (input[i] == '>')
			add_token(tokens, strdup(">"), REDIR_OUT), i++;
		else if (input[i] == '<')
			add_token(tokens, strdup("<"), REDIR_IN), i++;
		else if (input[i] == '|')
			add_token(tokens, strdup("|"), PIPE), i++;
		else if (input[i] == '"' || input[i] == '\'')
			handle_quote(input, &i, tokens);
		else
		{
			start = i;
			while (input[i] && !is_meta(input[i]))
				i++;
			add_token(tokens, substr(input, start, i - start), WORD);
		}
	}
}

// ---------- Parser ----------

t_redirect	*add_redirect(t_token **tokens, int type)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == WORD)
		redir->file = strdup((*tokens)->content);
	else
		redir->file = NULL;
	redir->next = NULL;
	return (redir);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd_head = NULL;
	t_command	*current = NULL;
	t_command	*new_cmd;
	t_redirect	*redir;
	int			i;

	while (tokens)
	{
		new_cmd = malloc(sizeof(t_command));
		new_cmd->args = malloc(sizeof(char *) * 256);
		new_cmd->redirects = NULL;
		new_cmd->next = NULL;
		i = 0;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == WORD)
				new_cmd->args[i++] = strdup(tokens->content);
			else if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
			{
				redir = add_redirect(&tokens, tokens->type);
				if (redir)
				{
					redir->next = new_cmd->redirects;
					new_cmd->redirects = redir;
				}
			}
			tokens = tokens->next;
		}
		new_cmd->args[i] = NULL;
		if (!cmd_head)
			cmd_head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmd_head);
}

// ---------- Debug Print ----------

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token:\t%-10s\t|\tType:\t%d\n", tokens->content, tokens->type);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *cmds)
{
	int			i;
	int			j;
	t_redirect	*redir;

	i = 0;
	while (cmds)
	{
		printf("Command\t%d:\n", i++);
		j = 0;
		while (cmds->args && cmds->args[j])
			printf("\tArg:\t%s\n", cmds->args[j++]);
		redir = cmds->redirects;
		while (redir)
		{
			printf("\tRedirect:\tType\t%d\t->\t%s\n", redir->type, redir->file);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

// ---------- Main ----------

int	main(void)
{
	t_token		*tokens = NULL;
	t_command	*cmds;
	char		*input;
	int			i;

	input = readline("minishell> ");
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			input[i] = '\t';
		i++;
	}
	lexer(input, &tokens);
	printf("=== TOKENS ===\n");
	print_tokens(tokens);
	printf("\n=== PARSED COMMANDS ===\n");
	cmds = parse_tokens(tokens);
	print_commands(cmds);
	return (0);
}
