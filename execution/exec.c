/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:01:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:54:43 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_shell *main, t_cmd *cmd)
{
	if (cmd->in == -1 || cmd->out == -1 || !cmd->cmd)
	{	
		cleanup(main, ft_exit_status(0, 0));
		ft_malloc(0, FREE);
	}
	ft_cls(cmd->pipe_fd[0]);
	if (cmd->out == -1337)
		cmd->out = cmd->pipe_fd[1];
	child_dup_in(main, cmd);
	child_dup_out(main, cmd);
	if (cmd->is_builtin == TRUE)
	{
		run_builtins(main, cmd->cmd);
		exit(ft_exit_status(0, 0));
	}
	execut_child_cmd(main, cmd);
}

void	ft_parent(t_cmd *cmd)
{
	if (cmd->next)
	{
		ft_cls(cmd->pipe_fd[1]);
		if (cmd->next->in == -1337)
			cmd->next->in = cmd->pipe_fd[0];
	}
	if (cmd->in != -1337)
		ft_cls(cmd->in);
	if (cmd->out != -1337)
		ft_cls(cmd->out);
}

void	flag_builtins(t_shell *main)
{
	t_cmd	*curr;

	curr = main->cmd;
	while (curr)
	{
		if (curr->cmd && curr->cmd[0] && is_builtin(curr->cmd[0]))
			curr->is_builtin = TRUE;
		else
			curr->is_builtin = FALSE;
		curr = curr->next;
	}
}

void	execute_shild(t_shell *main)
{
	int		i;
	t_cmd	*cur;

	main->pid = ft_malloc(main->nbr_cmd * sizeof(pid_t), MALLOC);
	if (main->pid == NULL)
		return ;
	i = 0;
	cur = main->cmd;
	while (i < main->nbr_cmd && cur)
	{
		if (cur->next)
			ft_creat_pipe(main, cur);
		ft_fork_process(main, i);
		if (main->pid[i] == 0)
		{	
			if (cur->fd_statuts == 1)
				exit(ft_exit_status(0, 0));
			ft_child(main, cur);
		}
		else
			ft_parent(cur);
		cur = cur->next;
		i++;
	}
}

void	exec_cmd(t_shell *main)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = main->cmd;
	if (cur->is_builtin && main->nbr_cmd == 1 && cur->fd_statuts != 1)
	{
		main->saved_fdout = dup(1);
		main->saved_fdin = dup(0);
		if (cur->in != -1337)
			dup2(cur->in, 0);
		if (cur->out != -1337)
			dup2(cur->out, 1);
		run_builtins(main, cur->cmd);
		dup2(main->saved_fdout, 1);
		ft_cls(main->saved_fdout);
		dup2(main->saved_fdin, 0);
		ft_cls(main->saved_fdin);
		return ;
	}
	else
	{
		execute_shild(main);
		wait_children(main);
	}
}
