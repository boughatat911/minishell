/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:24:49 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/25 16:27:43 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hundle_no_case(t_shell *main, char **cmd, int i)
{
	t_env	*env;
	size_t	len;

	env = main->env;
	len = ft_strlen(cmd[i]);
	while (env)
	{
		if (!ft_strncmp(env->content, cmd[i], len) && env->content[len] == '=')
			return ;
		env = env->next;
	}
	add_to_env(main, cmd[i]);
}

void	ft_plus_equal(t_env *env, char *cmd, int len, char *value)
{
	char	*old_value;
	char	*new_value;
	char	*new_content;

	if (env->content[len] != '=')
		old_value = "";
	else
		old_value = env->content + len + 1;
	new_value = ft_strjoin(old_value, value);
	new_content = ft_malloc(len + 1 + ft_strlen(new_value) + 1, MALLOC);
	ft_strncpy(new_content, cmd, len);
	new_content[len] = '=';
	ft_strcpy(new_value, new_content + len + 1);
	env->content = new_content;
}

int	ft_equal(t_shell *main, char *cmd, int len, int flag)
{
	t_env	*env;

	env = main->env;
	while (env)
	{
		if (!ft_strncmp(env->content, cmd, len)
			&& (env->content[len] == '=' || env->content[len] == '\0'))
		{
			flag = 1;
			env->content = ft_strdup(cmd);
			break ;
		}
		env = env->next;
	}
	return (flag);
}

void	my_export(t_shell *main, char **cmd)
{
	int		i;
	int		flag;

	i = 1;
	if (!cmd[1])
	{
		environment(main->env);
		return ;
	}
	while (cmd[i])
	{
		flag = is_invalide_indentifer(cmd[i]);
		if (flag != 1)
			hundle_export_args(main, cmd, i);
		i++;
	}
}

int	search_equal(char **array, int i)
{
	int	j;
	int	equal_pos;

	j = 0;
	equal_pos = -1;
	while (array[i][j])
	{
		if (array[i][j] == '=')
		{
			equal_pos = j;
			break ;
		}
		j++;
	}
	return (equal_pos);
}
