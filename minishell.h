/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ayameur <ayameur@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/28 16:56:37 by ayameur		   #+#	#+#			 */
/*   Updated: 2025/06/28 17:03:33 by ayameur		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE  1
# define FALSE 0

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	DILIMITER
}	t_token_type;
//---------------{ tokenization structure }-----------------
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	int				ex_space_flag;
	int				index;
	int				flag;
	struct s_token	*next;
}	t_token;

//---------------{ cmd structure }-----------------
typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	int				fd_statuts;
	int				heredoc_statuts;
	int				pipe_fd[2];
	int				is_builtin;
	int				flag_var;
	struct s_cmd	*next;
}	t_cmd;
//---------------{ env structure }-----------------
typedef struct s_env
{
	char			*content;
	int				index;
	int				flag;
	int				quot;
	struct s_env	*next;
}	t_env;
//---------------{ main structure }-----------------
typedef struct s_shell
{
	char			*content;
	t_token_type	type;
	t_token			*token;
	char			*tmp;
	t_env			*env;
	t_cmd			*cmd;
	char			**path_splited;
	int				nbr_cmd;
	int				fd;
	pid_t			*pid;
	int				saved_fdin;
	int				saved_fdout;
	int				get;
	int				new_pwd;
	int				exit_status;
	struct s_shell	*next;
}	t_shell;

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

typedef enum e_call
{
	FREE,
	MALLOC
}	t_call;

void		minishell(t_shell *shell_list, char **env);
int			ft_exit_status(int _status, int set);
t_malloc	*new_node(void	*ptr);
t_malloc	*last_node(t_malloc	**head);
void		add_back(t_malloc	**head, t_malloc *new);
void		clear_all(t_malloc **head);
void		*ft_malloc(size_t size, t_call call);
//---------------{ tokenization functions }-----------------
int			lexer_1(char *input, t_token **tokens);
void		lexer_2(t_token **tokens, char *input, int *i, int *index);
int			syntax_error(t_token **tokens);
//---------------{ cmd functions }-----------------
t_cmd		*ft_cmd(t_shell *shell, t_token **token);
void		handle_heredoc(t_shell *shell, char *delimiter,
				int fd, t_cmd *node);
t_token		*handle_redir_in(t_cmd *node, t_token *start);
t_token		*handle_redir_out(t_cmd *node, t_token *start);
t_token		*handle_redir_append(t_cmd *node, t_token *start);
t_token		*store_cmd_node(t_cmd *node_to_fill, t_token *start);
t_token		*handle_token_type(t_cmd *node, t_token *start);
t_token		*handle_heredoc_token(t_shell *shell, t_cmd *node, t_token *start);
void		ft_redirections(t_cmd *head);
void		ft_cmd_2(t_token *tmp, t_cmd *cmd_tmp);
char		*heredoc_expand(char *str, t_env *env);
int			ft_g1(char **cmd);
//---------------{ expand functions }-----------------
char		*cher_env(char *key, t_env *env, char quot);
char		*expand_env_var(char *str, int *i, t_env *env, char *res);
char		*ft_dolar(char *str);
char		*strjoin_char(char *str, char c);
char		*join_single_quot(char *str, int *i, char *res);
char		*handle_regular_quotes(char *str, int *i, char *res, char *quot);
char		*handle_var_expand(char *str, int *i, t_shell *shell, char *res);
char		*ft_expand_token(char *str, t_shell *shell, t_token *tok);
void		ft_expand(t_shell *shell);
int			is_special_char2(char c);
int			ft_quote(char c);
t_token		*split_token_ex(t_token *tok, char *str);
t_token		*split_to_token_list(t_token *tok, char **spl);
char		**ft_split_space(char *str);
char		*expand_env_var_her(char *str, int *i, t_env *env, char *res);
t_token		*token_up(t_token *token);
char		*up_token(char *str, int i);
size_t		ft_count_2d(char **arr);
char		*remove_quotes(char *str);
void		ft_skipe_delimiter(t_token *token);
int			len_n(int n);
void		delimiter_dollar(char *str, char *new, int *i, int *p);
char		*up_re_case(t_token *tok, char *str);
int			gg(char *str);
char		add_token_list(char *input, int *i, char quote_char);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstlast(t_env *lst);

t_cmd		*ft_lstnew_cmd(void);
t_cmd		*ft_lstlast_cmd(t_cmd *lst);
void		ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void		token_str(t_token **token, char *input, int *i, int *index);
void		add_token(t_token **lst, char *content,
				t_token_type type, int index);
t_token		*new_token(char *content, t_token_type type);
char		*substr(char *s, int start, int len);
t_env		*ft_env(t_env *env_list, char **env);
// ---------------general tools -----------------
char		*ft_strdup(const char *s1);	
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *dest, char *src, size_t n);
char		*ft_strcpy(const char *str, char *dest);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		**ft_strjoin2d(char **s1, char *s2);
char		**ft_split(const char *str, char c);
int			ft_isalpha(int c);
char		*ft_strstr(char *str, char *to_find);
int			ft_isalnum(int c);
char		*ft_strchr(const char *s, int c);
void		ft_putchar(char c);
int			ft_isdigit(int c);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			is_special_char(char c);
//		   BUILTINS
void		my_export(t_shell *main, char **cmd);
void		ft_plus_equal(t_env *env, char *cmd, int len, char *value);
int			ft_equal(t_shell *main, char *cmd, int len, int flag);
void		add_to_env(t_shell *main, char *new_var);
char		*my_getenv( t_shell *main, char *var_name);
void		update_env(t_shell *main, char *key, char *value);
int			my_cd(char **str, t_shell *main);
int			unset_env(t_shell *main, char **var_name);
int			my_echo(char **av);
int			my_pwd(t_shell *main);
int			my_exit(char **cmd);
void		run_builtins(t_shell *main, char **cmd);
int			is_builtin(char *str);
int			print_env(t_shell *main);
int			is_valid_var(char *str);
void		environment(t_env *env);
int			search_equal(char **array, int i);
char		**arrange_array(char **array);
int			is_invalide_indentifer(char *cmd);
int			plus_equal_hundle_case(t_shell *main, char *cmd);
int			hundle_equal_case(t_shell *main, char **cmd, int i);
void		hundle_export_args(t_shell *main, char **cmd, int i);
void		hundle_no_case(t_shell *main, char **cmd, int i);
void		remove_env_var(t_shell *main, char *var_name, size_t var_len);
int			ft_count_heredoc(t_token *tok);
void		handle_sigint(int sig);
void		signals_child(void);
void		printf_error(char *var, char *code, int sta);
void		ft_exit(t_shell *main, char *cmd);
void		ft_putstr_fd(char *s, int fd);
//			EXECUTION
void		get_path(t_shell *main);
void		check_if_access(t_shell *main);
void		ft_check_cmd_path(t_cmd *cmd, char **path);
void		ft_creat_pipe(t_shell *main, t_cmd *cmd);
void		ft_fork_process(t_shell *main, int i);
void		nbr_cmd(t_shell *main);
void		exec_cmd(t_shell *main);
int			is_builtin(char *str);
char		**env_in_2d(t_shell *main);
void		wait_children(t_shell *main);
void		flag_builtins(t_shell *main);
void		execution(t_shell *main);
void		setup_signals(void);
void		cleanup(t_shell *main, int status);
void		execut_child_cmd(t_shell *main, t_cmd *cmd);
void		child_dup_out(t_shell *main, t_cmd *cmd);
void		child_dup_in(t_shell *main, t_cmd *cmd);
int			ft_cls(int fd);

#endif
