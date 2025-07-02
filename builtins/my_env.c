/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:53:05 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_shell *main)
{
	t_env	*env;

	env = main->env;
	while (env)
	{
		if (ft_strchr(env->content, '='))
			printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}

int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (0);
			break ;
		}
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	printf_error(char *var, char *msg, int status)
{
	write(2, "minishell> ", 11);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
	ft_exit_status(status, 1);
}

void	cleanup(t_shell *main, int status)
{
	t_cmd	*cmd;

	cmd = main->cmd;
	while (cmd)
	{
		if (cmd->in != -1337)
			ft_cls(cmd->in);
		if (cmd->out != -1337)
			ft_cls(cmd->out);
		if (cmd->pipe_fd[0] > 2)
			ft_cls(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] > 3)
			ft_cls(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
	exit(ft_exit_status(status, 1));
}

void	ft_exit(t_shell *main, char *cmd)
{
	struct stat	file;

	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
	{	
		printf_error(cmd, "is a directory", 126);
		cleanup(main, 126);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{	
		printf_error(cmd, strerror(errno), 126);
		cleanup(main, 126);
	}
	else
	{	
		printf_error(cmd, "commande not found ", 127);
		cleanup(main, 127);
	}
}
