
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

static bool is_whitespace(char c)
{
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