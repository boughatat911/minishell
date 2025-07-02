NAME = minishell

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC =	minishell.c \
		parsing/token/tools.c \
		parsing/token/syntax_error.c \
		parsing/token/token.c \
		parsing/token/env.c \
		parsing/cmd/cmd.c \
		parsing/cmd/tools_1.c \
		parsing/cmd/tools_2.c \
		parsing/cmd/heredoc.c \
		parsing/cmd/redirection.c \
		parsing/expand/expand.c \
		parsing/expand/expand2.c \
		parsing/expand/tools_1.c \
		parsing/expand/tools_2.c \
		tools/ft_malloc.c \
		tools/tools_1.c \
		tools/tools_2.c \
		tools/tools_3.c \
		tools/tools_4.c \
		tools/tools_5.c \
		tools/tools_6.c \
		execution/check_path_cmd.c \
		execution/exec.c \
		execution/exec2.c \
		execution/builtins.c \
		execution/execution.c \
		execution/utils_execution.c \
		builtins/add_env.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/export.c \
		builtins/export2.c \
		builtins/export_utils.c \
		builtins/my_getenv.c \
		builtins/my_unset.c \
		builtins/update_env.c \
		builtins/my_pwd.c \
		builtins/my_env.c \
		builtins/my_exit.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c minishell.h
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
