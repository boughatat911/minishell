/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:44:03 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:55:19 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_dup_in(t_shell *main, t_cmd *cmd)
{
	if (cmd->in != -1)
	{
		if (dup2(cmd->in, 0) == -1)
		{
			perror("dup2\n");
			if (main)
				cleanup(main, ft_exit_status(0, 0));
			ft_malloc(0, FREE);
			exit(ft_exit_status(1, 1));
		}
		ft_cls(cmd->in);
	}
}

void	child_dup_out(t_shell *main, t_cmd *cmd)
{
	if (cmd->out != -1)
	{
		if (dup2(cmd->out, 1) == -1)
		{
			perror("dup2\n");
			if (main)
				cleanup(main, ft_exit_status(0, 0));
			ft_malloc(0, FREE);
			exit(ft_exit_status(1, 1));
		}
		ft_cls(cmd->out);
	}
}

void	execut_child_cmd(t_shell *main, t_cmd *cmd)
{
	signals_child();
	if (cmd->cmd && execve(cmd->cmd[0], cmd->cmd, env_in_2d(main)) == -1)
	{
		ft_exit(main, cmd->cmd[0]);
		ft_malloc(0, FREE);
		exit(ft_exit_status(1, 1));
	}
}
