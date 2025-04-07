#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef enum e_token_type {
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
    struct s_token *next;
} t_token;

t_token *new_token(char *content, t_token_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok)
        return NULL;
    tok->content = content;
    tok->type = type;
    tok->next = NULL;
    return tok;
}

void add_token(t_token **lst, char *content, t_token_type type)
{
    t_token *tok = new_token(content, type);
    if (!*lst)
        *lst = tok;
    else {
        t_token *tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = tok;
    }
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

void lexer(char *input, t_token **tokens)
{
    int i = 0;
    while (input[i])
    {
        if (input[i] == ' ')
            i++;
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            add_token(tokens, strdup(">>"), APPEND);
            i += 2;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            add_token(tokens, strdup("<<"), HEREDOC);
            i += 2;
        }
        else if (input[i] == '>')
        {
            add_token(tokens, strdup(">"), REDIR_OUT);
            i++;
        }
        else if (input[i] == '<')
        {
            add_token(tokens, strdup("<"), REDIR_IN);
            i++;
        }
        else if (input[i] == '|')
        {
            add_token(tokens, strdup("|"), PIPE);
            i++;
        }
        else if (input[i] == '"' || input[i] == '\'')
        {
            char quote = input[i++];
            int start = i;
            while (input[i] && input[i] != quote)
                i++;
            add_token(tokens, substr(input, start, i - start), WORD);
            if (input[i] == quote)
                i++;
        }
        else
        {
            int start = i;
            while (input[i] && input[i] != ' ' && input[i] != '|' &&
                   input[i] != '<' && input[i] != '>' &&
                   input[i] != '"' && input[i] != '\'')
                i++;
            add_token(tokens, substr(input, start, i - start), WORD);
        }
    }
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("Token: %-12s | Type: %d\n", tokens->content, tokens->type);
        tokens = tokens->next;
    }
}

int main()
{
    char *input = readline("minishell> ");
    t_token *tokens = NULL;

    lexer(input, &tokens);
    print_tokens(tokens);

    return 0;
}
