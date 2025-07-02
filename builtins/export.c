/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/29 13:27:37 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_invalide_indentifer(char *cmd)
{
	int	i;

	i = 0;
	if (!is_valid_var(cmd))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		ft_exit_status(1, 1);
		return (1);
	}
	return (0);
}

void	plus_equal_add_new(t_shell *main, char *cmd, char *value)
{
	int		eq;
	char	*new_value;

	eq = find_equal(cmd);
	new_value = substr(cmd, 0, eq -1);
	new_value = ft_strjoin(new_value, "=");
	new_value = ft_strjoin(new_value, value);
	add_to_env(main, new_value);
}

int	plus_equal_hundle_case(t_shell *main, char *cmd)
{
	char	*value;
	char	*plus_equal;
	t_env	*env;
	size_t	len;

	plus_equal = ft_strstr(cmd, "+=");
	len = plus_equal - cmd;
	value = plus_equal + 2;
	if (len == 0)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	env = main->env;
	while (env)
	{
		if (!ft_strncmp(env->content, cmd, len)
			&& (env->content[len] == '=' || env->content[len] == '\0'))
		{
			ft_plus_equal(env, cmd, len, value);
			return (1);
		}
		env = env->next;
	}
	plus_equal_add_new(main, cmd, value);
	return (1);
}

int	hundle_equal_case(t_shell *main, char **cmd, int i)
{
	int		flag;
	char	*eq_pos;
	size_t	len;

	flag = 0;
	eq_pos = ft_strchr(cmd[i], '=');
	if (eq_pos)
		len = eq_pos - cmd[i];
	else
		len = ft_strlen(cmd[i]);
	if (len == 0)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	flag = ft_equal(main, cmd[i], len, 0);
	if (!flag)
		add_to_env(main, cmd[i]);
	return (1);
}
