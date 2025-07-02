/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:54:19 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(t_shell *main, char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		ft_exit_status(my_cd(cmd, main), 1);
	if (!ft_strcmp(cmd[0], "env"))
		ft_exit_status(print_env(main), 1);
	if (!ft_strcmp(cmd[0], "export"))
		my_export(main, cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_exit_status(my_pwd(main), 1);
	if (!ft_strcmp(cmd[0], "unset"))
		ft_exit_status(unset_env(main, cmd), 1);
	if (!ft_strcmp(cmd[0], "echo"))
		ft_exit_status(my_echo(cmd), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit_status(my_exit(cmd), 1);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "exit"))
		return (TRUE);
	return (FALSE);
}
