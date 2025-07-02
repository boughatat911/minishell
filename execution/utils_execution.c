/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:34:59 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:55:32 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_children(t_shell *main)
{
	int	i;
	int	status;

	i = -1;
	while (++i < main->nbr_cmd)
	{
		if (waitpid(main->pid[i], &status, 0) == -1)
			ft_exit(main, main->cmd->cmd[0]);
	}
	if (WIFEXITED(status))
		ft_exit_status(WEXITSTATUS(status), 1);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{	
		ft_exit_status(130, 1);
		write (1, "\n", 1);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_exit_status(131, 1);
		write (1, "Quit (core dumped)\n", 19);
	}
	setup_signals();
}

void	ft_creat_pipe(t_shell *main, t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe filled\n");
		cleanup(main, ft_exit_status(0, 0));
		ft_malloc(0, FREE);
		exit(ft_exit_status(1, 1));
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(130, 1);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
