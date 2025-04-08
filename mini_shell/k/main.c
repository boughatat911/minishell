#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n");
	while (tokens)
	{
		printf("Type: ");
		switch (tokens->type)
		{
			case T_WORD:
				printf("WORD");
				break;
			case T_PIPE:
				printf("PIPE");
				break;
			case T_REDIR_IN:
				printf("REDIR_IN");
				break;
			case T_REDIR_OUT:
				printf("REDIR_OUT");
				break;
			case T_REDIR_APPEND:
				printf("REDIR_APPEND");
				break;
			case T_WHITESPACE:
				printf("WHITESPACE");
				break;
			case T_SQUOTE:
				printf("SQUOTE");
				break;
			case T_DQUOTE:
				printf("DQUOTE");
				break;
			case T_DOLLAR:
				printf("DOLLAR");
				break;
			case T_END:
				printf("END");
				break;
		}
		printf(", Value: '%s'\n", tokens->value);
		tokens = tokens->next;
	}
}

static void	print_commands(t_cmd *cmd)
{
	int	i;

	printf("\nCommands:\n");
	while (cmd)
	{
		printf("Command:\n");
		printf("  Args: ");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("'%s' ", cmd->args[i]);
				i++;
			}
		}
		printf("\n");
		printf("  Redirections:\n");
		if (cmd->redirs)
		{
			t_redir *redir = cmd->redirs;
			while (redir)
			{
				printf("    Type: %d, File: '%s'\n", redir->type, redir->file);
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
}

static void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (*input)
		{
			add_history(input);
			tokens = tokenize_input(input);
			if (tokens)
			{
				print_tokens(tokens);
				cmd = parse_commands(tokens);
				if (cmd)
				{
					print_commands(cmd);
					free_cmd_list(cmd);
				}
				free_tokens(tokens);
			}
		}
		free(input);
	}
	printf("exit\n");
	return (0);
} 