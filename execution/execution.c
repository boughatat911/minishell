/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:55:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_shell *main)
{
	t_cmd	*tmp;

	tmp = main->cmd;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->heredoc_statuts == 911)
			return ;
		tmp = tmp->next;
	}
	nbr_cmd(main);
	get_path(main);
	flag_builtins(main);
	check_if_access(main);
	exec_cmd(main);
}

void	ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		perror("fork failed");
		cleanup(main, ft_exit_status(0, 0));
		ft_malloc(0, FREE);
		exit(ft_exit_status(1, 1));
	}
}
