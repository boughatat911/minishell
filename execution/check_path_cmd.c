/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 15:20:07 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path(t_shell *main)
{
	t_env	*cur;
	char	*path;

	cur = main->env;
	path = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->content, "PATH=", 5) == 0)
		{
			path = cur->content + 5;
			break ;
		}
		cur = cur->next;
	}
	if (path == NULL || *path == '\0')
	{	
		main->path_splited = NULL;
		return ;
	}
	main->path_splited = ft_split(path, ':');
}

void	check_if_access(t_shell *main)
{
	t_cmd	*cmd;
	t_env	*env;

	cmd = main->cmd;
	env = main->env;
	while (cmd)
	{
		if (cmd->is_builtin)
			cmd = cmd->next;
		else
		{
			if (cmd->cmd && cmd->cmd[0]
				&& access(cmd->cmd[0], F_OK) == 0)
				cmd = cmd->next;
			else
			{
				ft_check_cmd_path(cmd, main->path_splited);
				cmd = cmd->next;
			}
		}
	}
}

void	ft_check_cmd_path(t_cmd *cmd, char **path)
{
	int		i;
	char	*res;
	char	*tmp;
	t_cmd	*cur;

	i = 0;
	cur = cmd;
	while (path && path[i] && cur->cmd)
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return ;
		res = ft_strjoin(tmp, cur->cmd[0]);
		if (!res)
			return ;
		if (access(res, X_OK | F_OK) == 0)
		{
			cur->cmd[0] = res;
			break ;
		}
		i++;
	}
}

void	nbr_cmd(t_shell *main)
{
	t_cmd	*cur;
	int		count;

	cur = main->cmd;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	main->nbr_cmd = count;
}
