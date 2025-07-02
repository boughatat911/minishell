/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:13:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/26 19:19:27 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_target_dir(char **str, t_shell *main)
{
	char	*target_dir;

	if (str[1])
		target_dir = str[1];
	else
	{
		target_dir = my_getenv(main, "HOME");
		if (target_dir == NULL)
		{
			perror("cd\n");
			return (NULL);
		}
	}
	return (target_dir);
}

int	change_dir( t_shell *main, char *target_dir, char **oldpwd, char **newpwd)
{
	char	*tmp;

	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
	{
		main->get = 1;
		*oldpwd = ft_strdup(my_getenv(main, "PWD"));
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
	}
	*newpwd = getcwd(NULL, 0);
	if (!*newpwd)
	{
		main->new_pwd = 1;
		printf("cd: error retrieving current directory: \n");
		printf("getcwd: cannot access parent directories\n");
		*newpwd = ft_strdup(my_getenv(main, "PWD"));
		tmp = ft_strjoin(*newpwd, "/");
		*newpwd = ft_strjoin(tmp, target_dir);
		update_env(main, "PWD", *newpwd);
		return (1);
	}
	return (0);
}

void	update_dir_env(t_shell *main, char *oldpwd, char *newpwd)
{
	update_env(main, "OLDPWD", oldpwd);
	update_env(main, "PWD", newpwd);
}

int	my_cd(char **str, t_shell *main)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target_dir;

	main->get = 0;
	main->new_pwd = 0;
	target_dir = get_target_dir(str, main);
	if (!target_dir)
		return (1);
	change_dir(main, target_dir, &oldpwd, &newpwd);
	update_dir_env(main, oldpwd, newpwd);
	if (!main->get)
		free(oldpwd);
	if (!main->new_pwd)
		free(newpwd);
	return (0);
}
