#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_WHITESPACE,
	T_SQUOTE,
	T_DQUOTE,
	T_DOLLAR,
	T_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				pipe_fd[2];
	int				in_fd;
	int				out_fd;
	struct s_cmd	*next;
}	t_cmd;

// Token functions
t_token		*tokenize_input(char *input);
void		free_tokens(t_token *tokens);

// Command parsing
t_cmd		*parse_commands(t_token *tokens);
void		free_cmd_list(t_cmd *cmd);

// Redirection handling
void		free_redirs(t_redir *redirs);

// Utils
char		*ft_strndup(const char *s, size_t n);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

#endif 