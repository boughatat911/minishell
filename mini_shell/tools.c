// // // #include <stdlib.h>
// // // #include <string.h>
// // // #include <stdio.h>
// // // #include <ctype.h>

// // // typedef struct s_cmd {
// // // 	char **argv;
// // // 	char *infile;
// // // 	char *outfile;
// // // 	int append;
// // // 	struct s_cmd *next;
// // // } t_cmd;

// // // static void skip_spaces(char **s)
// // // {
// // // 	while (**s && isspace(**s))
// // // 		(*s)++;
// // // }

// // // char **split_pipes(char *input)
// // // {
// // // 	char **result = malloc(sizeof(char *) * 10);
// // // 	int i = 0, start = 0, j = 0;
// // // 	int dquote = 0, squote = 0;

// // // 	while (input[i])
// // // 	{
// // // 		if (input[i] == '"' && squote == 0) {
// // // 			if (dquote == 0)
// // // 				dquote = 1;
// // // 			else
// // // 				dquote = 0;
// // // 		}
// // // 		if (input[i] == '\'' && dquote == 0) {
// // // 			if (squote == 0)
// // // 				squote = 1;
// // // 			else
// // // 				squote = 0;
// // // 		}
// // // 		if (input[i] == '|' && !dquote && !squote)
// // // 		{
// // // 			result[j++] = strndup(&input[start], i - start);
// // // 			start = i + 1;
// // // 		}
// // // 		i++;
// // // 	}
// // // 	if (i > start)
// // // 		result[j++] = strndup(&input[start], i - start);
// // // 	result[j] = NULL;
// // // 	return result;
// // // }

// // // char **split_words(char *str)
// // // {
// // // 	char **out = malloc(sizeof(char *) * 100);
// // // 	int i = 0, j = 0;
// // // 	while (*str)
// // // 	{
// // // 		skip_spaces(&str);
// // // 		if (!*str) break;
// // // 		char *start = str;
// // // 		int len = 0;
// // // 		if (*str == '"' || *str == '\'') {
// // // 			char quote = *str++;
// // // 			start = str;
// // // 			while (*str && *str != quote) str++, len++;
// // // 			out[j++] = strndup(start, len);
// // // 			if (*str) str++;
// // // 		} else {
// // // 			while (str[len] && !isspace(str[len]) && str[len] != '>' && str[len] != '<') len++;
// // // 			out[j++] = strndup(str, len);
// // // 			str += len;
// // // 		}
// // // 	}
// // // 	out[j] = NULL;
// // // 	return out;
// // // }

// // // t_cmd *parse_command(char *line)
// // // {
// // // 	t_cmd *cmd = calloc(1, sizeof(t_cmd));
// // // 	char **words = split_words(line);

// // // 	cmd->argv = malloc(sizeof(char *) * 100);
// // // 	int i = 0, a = 0;
// // // 	while (words[i])
// // // 	{
// // // 		if (strcmp(words[i], ">") == 0 && words[i + 1])
// // // 			cmd->outfile = strdup(words[++i]);
// // // 		else if (strcmp(words[i], ">>") == 0 && words[i + 1])
// // // 		{
// // // 			cmd->outfile = strdup(words[++i]);
// // // 			cmd->append = 1;
// // // 		}
// // // 		else if (strcmp(words[i], "<") == 0 && words[i + 1])
// // // 			cmd->infile = strdup(words[++i]);
// // // 		else
// // // 			cmd->argv[a++] = strdup(words[i]);
// // // 		i++;
// // // 	}
// // // 	cmd->argv[a] = NULL;
// // // 	return cmd;
// // // }

// // // t_cmd *parse_input(char *input)
// // // {
// // // 	char **parts = split_pipes(input);
// // // 	t_cmd *head = NULL, *prev = NULL;
// // // 	int i = 0;

// // // 	while (parts[i])
// // // 	{
// // // 		t_cmd *node = parse_command(parts[i]);
// // // 		if (!head)
// // // 			head = node;
// // // 		else
// // // 			prev->next = node;
// // // 		prev = node;
// // // 		i++;
// // // 	}
// // // 	return head;
// // // }

// // // void print_cmds(t_cmd *cmd)
// // // {
// // // 	int i = 1;
// // // 	while (cmd)
// // // 	{
// // // 		printf("---- CMD %d ----\n", i++);
// // // 		int j = 0;
// // // 		while (cmd->argv && cmd->argv[j])
// // // 		{
// // // 			printf("arg[%d]: %s\n", j, cmd->argv[j]);
// // // 			j++;
// // // 		}
// // // 		if (cmd->infile)
// // // 			printf("infile: %s\n", cmd->infile);
// // // 		if (cmd->outfile)
// // // 			printf("outfile: %s (append: %d)\n", cmd->outfile, cmd->append);
// // // 		cmd = cmd->next;
// // // 	}
// // // }

// // // // Function to free the commands list and its members
// // // void free_cmds(t_cmd *cmd)
// // // {
// // // 	t_cmd *tmp;
// // // 	while (cmd)
// // // 	{
// // // 		tmp = cmd;
// // // 		if (cmd->argv)
// // // 		{
// // // 			for (int i = 0; cmd->argv[i]; i++)
// // // 				free(cmd->argv[i]);
// // // 			free(cmd->argv);
// // // 		}
// // // 		if (cmd->infile)
// // // 			free(cmd->infile);
// // // 		if (cmd->outfile)
// // // 			free(cmd->outfile);
// // // 		cmd = cmd->next;
// // // 		free(tmp);
// // // 	}
// // // }

// // // int main(void)
// // // {
// // // 	char *input = "cat file.txt | grep \"hello | world\" >> out.txt";

// // // 	// Check if input is empty
// // // 	if (input == NULL || *input == '\0') {
// // // 		printf("No input provided\n");
// // // 		return 1;
// // // 	}

// // // 	// Parse input and get commands
// // // 	t_cmd *cmds = parse_input(input);
// // // 	print_cmds(cmds); // helper to see structure

// // // 	// Free allocated memory
// // // 	free_cmds(cmds);

// // // 	return 0;
// // // }
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>

// // // ---------------------- TOKEN STRUCTURES ------------------------

// // typedef enum e_token_type
// // {
// //     WORD,
// //     PIPE,
// //     REDIRECT_IN,
// //     REDIRECT_OUT,
// //     REDIRECT_APPEND,
// //     HEREDOC
// // } t_token_type;

// // typedef struct s_token
// // {
// //     char *value;
// //     t_token_type type;
// //     struct s_token *next;
// // } t_token;

// // // ---------------------- TOKEN FUNCTIONS ------------------------

// // char *ft_substr(const char *s, int start, int len)
// // {
// //     char *substr = malloc(len + 1);
// //     if (!substr) return NULL;
// //     strncpy(substr, s + start, len);
// //     substr[len] = '\0';
// //     return substr;
// // }

// // t_token *create_token(char *value, t_token_type type)
// // {
// //     t_token *token = malloc(sizeof(t_token));
// //     token->value = strdup(value);
// //     token->type = type;
// //     token->next = NULL;
// //     return token;
// // }

// // void add_token(t_token **head, char *value, t_token_type type)
// // {
// //     t_token *new = create_token(value, type);
// //     if (!*head)
// //         *head = new;
// //     else
// //     {
// //         t_token *tmp = *head;
// //         while (tmp->next)
// //             tmp = tmp->next;
// //         tmp->next = new;
// //     }
// // }

// // // ---------------------- LEXER FUNCTION ------------------------

// // void lexer(char *input, t_token **token_list)
// // {
// //     int i = 0;

// //     while (input[i])
// //     {
// //         // Skip spaces
// //         if (input[i] == ' ')
// //         {
// //             i++;
// //         }

// //         // PIPE
// //         else if (input[i] == '|')
// //         {
// //             add_token(token_list, "|", PIPE);
// //             i++;
// //         }

// //         // REDIRECTION
// //         else if (input[i] == '>' || input[i] == '<')
// //         {
// //             if (input[i] == '>' && input[i + 1] == '>')
// //             {
// //                 add_token(token_list, ">>", REDIRECT_APPEND);
// //                 i += 2;
// //             }
// //             else if (input[i] == '<' && input[i + 1] == '<')
// //             {
// //                 add_token(token_list, "<<", HEREDOC);
// //                 i += 2;
// //             }
// //             else if (input[i] == '>')
// //             {
// //                 add_token(token_list, ">", REDIRECT_OUT);
// //                 i++;
// //             }
// //             else if (input[i] == '<')
// //             {
// //                 add_token(token_list, "<", REDIRECT_IN);
// //                 i++;
// //             }
// //         }

// //         // QUOTES
// //         else if (input[i] == '"' || input[i] == '\'')
// //         {
// //             char quote = input[i++];  // save the opening quote
// //             int start = i;
// //             while (input[i] && input[i] != quote)
// //                 i++;
            
// //             if (input[i] == quote)
// //             {
// //                 int len = i - start;
// //                 char *quoted = ft_substr(input, start, len);
// //                 add_token(token_list, quoted, WORD);
// //                 free(quoted);
// //                 i++; // skip closing quote
// //             }
// //             else
// //             {
// //                 // Unclosed quote: we consider the rest as part of the token (bash behavior)
// //                 char *quoted = strdup(&input[start - 1]);
// //                 add_token(token_list, quoted, WORD);
// //                 free(quoted);
// //                 return;
// //             }
// //         }

// //         // WORD
// //         else
// //         {
// //             int start = i;
// //             while (input[i] && input[i] != ' ' && input[i] != '|' &&
// //                    input[i] != '>' && input[i] != '<' &&
// //                    input[i] != '"' && input[i] != '\'')
// //                 i++;
// //             int len = i - start;
// //             char *word = ft_substr(input, start, len);
// //             add_token(token_list, word, WORD);
// //             free(word);
// //         }
// //     }
// // }

// // // ---------------------- PRINT TOKENS (DEBUG) ------------------------

// // void print_tokens(t_token *head)
// // {
// //     while (head)
// //     {
// //         printf("Token: %-20s | Type: %d\n", head->value, head->type);
// //         head = head->next;
// //     }
// // }

// // // ---------------------- MAIN ------------------------

// // int main()
// // {
// //     char input[1024];
// //     t_token *tokens = NULL;

// //     printf("minishell> ");
// //     if (fgets(input, sizeof(input), stdin))
// //     {
// //         input[strcspn(input, "\n")] = 0; // Remove newline
// //         lexer(input, &tokens);
// //         print_tokens(tokens);
// //     }

// //     // free tokens (not implemented here for brevity)

// //     return 0;
// // }

// #include <stdlib.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include <string.h>

// /* ===================== */
// /*     Token Defines     */
// /* ===================== */

// typedef enum e_token_type {
//     T_WORD,         // Regular command/argument
//     T_PIPE,         // |
//     T_REDIR_OUT,    // >
//     T_REDIR_IN,     // <
//     T_REDIR_APPEND, // >>
//     T_REDIR_HEREDOC,// <<
//     T_SQUOTE,       // '...' (single quoted)
//     T_DQUOTE,       // "..." (double quoted)
//     T_EOF           // End of input
// } t_token_type;

// typedef struct s_token {
//     t_token_type   type;
//     char          *value;
//     struct s_token *next;
// } t_token;

// /* ===================== */
// /*     Helper Functions  */
// /* ===================== */

// static bool is_whitespace(char c)
// {
//     return (c == ' ' || c == '\t' || c == '\n');
// }

// static bool is_operator(char c)
// {
//     return (c == '|' || c == '>' || c == '<');
// }

// static char *ft_strdup(const char *s)
// {
//     char *dup = malloc(strlen(s) + 1);
//     if (dup)
//         strcpy(dup, s);
//     return dup;
// }

// static char *ft_substr(const char *s, int start, int len)
// {
//     char *sub = malloc(len + 1);
//     if (sub) {
//         strncpy(sub, s + start, len);
//         sub[len] = '\0';
//     }
//     return sub;
// }

// /* ===================== */
// /*    Token Creation     */
// /* ===================== */

// t_token *create_token(t_token_type type, char *value)
// {
//     t_token *token = malloc(sizeof(t_token));
//     if (!token)
//         return NULL;
    
//     token->type = type;
//     token->value = value;
//     token->next = NULL;
//     return token;
// }

// void add_token(t_token **tokens, t_token **last, t_token *new)
// {
//     if (!*tokens)
//         *tokens = new;
//     else
//         (*last)->next = new;
//     *last = new;
// }

// /* ===================== */
// /*    Token Handlers     */
// /* ===================== */

// t_token *handle_operator(const char *input, int *i)
// {
//     if (input[*i] == '|') {
//         (*i)++;
//         return create_token(T_PIPE, ft_strdup("|"));
//     }
//     else if (input[*i] == '>' && input[*i + 1] == '>') {
//         *i += 2;
//         return create_token(T_REDIR_APPEND, ft_strdup(">>"));
//     }
//     else if (input[*i] == '>') {
//         (*i)++;
//         return create_token(T_REDIR_OUT, ft_strdup(">"));
//     }
//     else if (input[*i] == '<' && input[*i + 1] == '<') {
//         *i += 2;
//         return create_token(T_REDIR_HEREDOC, ft_strdup("<<"));
//     }
//     else if (input[*i] == '<') {
//         (*i)++;
//         return create_token(T_REDIR_IN, ft_strdup("<"));
//     }
//     return NULL;
// }

// t_token *handle_quote(const char *input, int *i)
// {
//     char quote = input[*i];
//     int start = ++(*i);
    
//     while (input[*i] && input[*i] != quote)
//         (*i)++;
    
//     if (!input[*i]) {
//         write(2, "Error: Unclosed quote\n", 21);
//         return NULL;
//     }
    
//     char *value = ft_substr(input, start, *i - start);
//     (*i)++;
//     return create_token(
//         quote == '\'' ? T_SQUOTE : T_DQUOTE,
//         value
//     );
// }

// t_token *handle_word(const char *input, int *i)
// {
//     int start = *i;
    
//     while (input[*i] && !is_whitespace(input[*i]) 
//         && !is_operator(input[*i]) && input[*i] != '\'' 
//         && input[*i] != '\"')
//     {
//         (*i)++;
//     }
    
//     char *value = ft_substr(input, start, *i - start);
//     return create_token(T_WORD, value);
// }

// /* ===================== */
// /*    Main Tokenizer     */
// /* ===================== */

// t_token *tokenize(const char *input)
// {
//     t_token *tokens = NULL;
//     t_token *last = NULL;
//     int i = 0;
    
//     while (input[i])
//     {
//         if (is_whitespace(input[i])) {
//             i++;
//             continue;
//         }
//         if (is_operator(input[i])) {
//             t_token *op = handle_operator(input, &i);
//             if (op) add_token(&tokens, &last, op);
//             continue;
//         }
//         if (input[i] == '\'' || input[i] == '\"') {
//             t_token *quote = handle_quote(input, &i);
//             if (quote) add_token(&tokens, &last, quote);
//             continue;
//         }
//         t_token *word = handle_word(input, &i);
//         add_token(&tokens, &last, word);
//     }
//     add_token(&tokens, &last, create_token(T_EOF, NULL));
//     return tokens;
// }

// /* ===================== */
// /*    Memory Cleanup     */
// /* ===================== */

// void free_tokens(t_token *tokens)
// {
//     t_token *tmp;
    
//     while (tokens)
//     {
//         tmp = tokens->next;
//         free(tokens->value);
//         free(tokens);
//         tokens = tmp;
//     }
// }

// /* ===================== */
// /*    Testing Function   */
// /* ===================== */

// void print_tokens(t_token *tokens)
// {
//     const char *type_names[] = {
//         "WORD", "PIPE", "REDIR_OUT", "REDIR_IN",
//         "REDIR_APPEND", "REDIR_HEREDOC",
//         "SQUOTE", "DQUOTE", "EOF"
//     };
    
//     while (tokens)
//     {
//         printf("[%s] %s\n", 
//               type_names[tokens->type],
//               tokens->value ? tokens->value : "(null)");
//         tokens = tokens->next;
//     }
// }

// int main(void)
// {
//     char *input = "echo \'\"hello swor''ld\"\' | grep hello > file.txt";
//     t_token *tokens = tokenize(input);
    
//     printf("Input: \"%s\"\n", input);
//     printf("Tokens:\n");
//     print_tokens(tokens);
    
//     free_tokens(tokens);
//     return 0;
// }

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/* ===================== */
/*     Token Defines     */
/* ===================== */

typedef enum e_token_type {
    T_WORD,         // Regular command/argument
    T_PIPE,         // |
    T_REDIR_OUT,    // >
    T_REDIR_IN,     // <
    T_REDIR_APPEND, // >>
    T_REDIR_HEREDOC,// <<
    T_SQUOTE,       // '...' (single quoted)
    T_DQUOTE,       // "..." (double quoted)
    T_EOF           // End of input
} t_token_type;

typedef struct s_token {
    t_token_type   type;
    char          *value;
    struct s_token *next;
} t_token;

/* ===================== */
/*     Helper Functions  */
/* ===================== */

static bool is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

static bool is_operator(char c) {
    return (c == '|' || c == '>' || c == '<');
}

static char *ft_strdup(const char *s) {
    char *dup = malloc(strlen(s) + 1);
    if (dup)
        strcpy(dup, s);
    return dup;
}

static char *ft_substr(const char *s, int start, int len) {
    char *sub = malloc(len + 1);
    if (sub) {
        strncpy(sub, s + start, len);
        sub[len] = '\0';
    }
    return sub;
}

/* ===================== */
/*    Token Creation     */
/* ===================== */

t_token *create_token(t_token_type type, char *value) {
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    
    token->type = type;
    token->value = value;
    token->next = NULL;
    return token;
}

void add_token(t_token **tokens, t_token **last, t_token *new) {
    if (!*tokens)
        *tokens = new;
    else
        (*last)->next = new;
    *last = new;
}

/* ===================== */
/*    Token Handlers     */
/* ===================== */

t_token *handle_operator(const char *input, int *i) {
    if (input[*i] == '|') {
        (*i)++;
        return create_token(T_PIPE, ft_strdup("|"));
    }
    else if (input[*i] == '>' && input[*i + 1] == '>') {
        *i += 2;
        return create_token(T_REDIR_APPEND, ft_strdup(">>"));
    }
    else if (input[*i] == '>') {
        (*i)++;
        return create_token(T_REDIR_OUT, ft_strdup(">"));
    }
    else if (input[*i] == '<' && input[*i + 1] == '<') {
        *i += 2;
        return create_token(T_REDIR_HEREDOC, ft_strdup("<<"));
    }
    else if (input[*i] == '<') {
        (*i)++;
        return create_token(T_REDIR_IN, ft_strdup("<"));
    }
    return NULL;
}

t_token *handle_quote(const char *input, int *i) 
{
    char quote = input[*i];
    int start = ++(*i);
    
    while (input[*i] && input[*i] != quote)
        (*i)++;
    
    if (!input[*i]) {
        write(2, "Error: Unclosed quote\n", 21);
        return NULL;
    }
    
    char *value = ft_substr(input, start, *i - start);
    (*i)++;
    return create_token(
        quote == '\'' ? T_SQUOTE : T_DQUOTE,
        value
    );
}

t_token *handle_word(const char *input, int *i) {
    int start = *i;
    
    while (input[*i] && !is_whitespace(input[*i]) 
        && !is_operator(input[*i]) && input[*i] != '\'' 
        && input[*i] != '\"')
    {
        (*i)++;
    }
    
    char *value = ft_substr(input, start, *i - start);
    return create_token(T_WORD, value);
}

/* ===================== */
/*    Main Tokenizer     */
/* ===================== */

t_token *tokenize(const char *input) {
    t_token *tokens = NULL;
    t_token *last = NULL;
    int i = 0;
    
    while (input[i]) {
        if (is_whitespace(input[i])) {
            i++;
            continue;
        }
        if (is_operator(input[i])) {
            t_token *op = handle_operator(input, &i);
            if (op) add_token(&tokens, &last, op);
            continue;
        }
        if (input[i] == '\'' || input[i] == '\"') {
            t_token *quote = handle_quote(input, &i);
            if (quote) add_token(&tokens, &last, quote);
            continue;
        }
        t_token *word = handle_word(input, &i);
        add_token(&tokens, &last, word);
    }
    add_token(&tokens, &last, create_token(T_EOF, NULL));
    return tokens;
}

/* ===================== */
/*    Memory Cleanup     */
/* ===================== */

void free_tokens(t_token *tokens) {
    t_token *tmp;
    
    while (tokens)
	{
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}

/* ===================== */
/*    Display Tokens     */
/* ===================== */

void print_tokens(t_token *tokens) {
    const char *type_names[] = {
        "WORD", "PIPE", "REDIR_OUT", "REDIR_IN",
        "REDIR_APPEND", "REDIR_HEREDOC",
        "SQUOTE", "DQUOTE", "EOF"
    };
    
    printf("=== Tokenized Output ===\n");
    while (tokens) {
        printf("[%-12s] %s\n", 
              type_names[tokens->type],
              tokens->value ? tokens->value : "(null)");
        tokens = tokens->next;
    }
    printf("=======================\n");
}

/* ===================== */
/*    Main Shell Loop    */
/* ===================== */

void minishell_loop(void) {
    char *input;
    t_token *tokens;

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            printf("exit\n");
            break;
        }
        if (strlen(input) > 0) {
            add_history(input);
            tokens = tokenize(input);
            print_tokens(tokens);
            free_tokens(tokens);
        }
        free(input);
    }
}

int main(void) {
    minishell_loop();
    return 0;
}