/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:58:59 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 18:11:52 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_null(t_shell *shell)
{
	shell->token = NULL;
	shell->cmd = NULL;
}

void	close_all_fds(t_shell *shell)
{
	t_cmd	*head;

	head = shell->cmd;
	while (head)
	{
		if (head->pipe_fd[0])
			ft_cls(head->pipe_fd[0]);
		if (head->in != -1337)
			ft_cls(head->in);
		if (head->out != -1337)
			ft_cls(head->out);
		head = head->next;
	}
}

void	minishell(t_shell *shell_list, char **env)
{
	char	*input;

	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	shell_list->env = ft_env(shell_list->env, env);
	while (TRUE)
	{
		input = readline("minishell> ");
		if (!input)
			(printf("exit\n"), ft_malloc(0, FREE), exit(ft_exit_status(0, 0)));
		if (input)
		{
			ft_null(shell_list);
			add_history(input);
			lexer_1(input, &shell_list->token);
			if (syntax_error(&shell_list->token) == TRUE)
			{
				ft_skipe_delimiter(shell_list->token);
				ft_expand(shell_list);
				shell_list->cmd = ft_cmd(shell_list, &shell_list->token);
				execution(shell_list);
			}
			close_all_fds(shell_list);
		}
		free(input);
	}
}

int	ft_exit_status(int _status, int set)
{
	static int	e_status;

	if (set)
		e_status = _status;
	return (e_status);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell_list;

	(void)ac;
	(void)av;
	shell_list = NULL;
	if (isatty(0) == 0)
		exit(0);
	setup_signals();
	minishell(shell_list, env);
	return (0);
}
