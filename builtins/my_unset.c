/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:06:40 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/27 15:00:30 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_env(t_shell *main, char **var_name)
{
	size_t	var_len;
	int		i;

	i = 1;
	while (var_name[i])
	{
		var_len = ft_strlen(var_name[i]);
		remove_env_var(main, var_name[i], var_len);
		i++;
	}
	return (1);
}

void	remove_env_var(t_shell *main, char *var_name, size_t var_len)
{
	t_env	*cur;
	t_env	*prev;

	cur = main->env;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->content, var_name, var_len) == 0
			&& (cur->content[var_len] == '='
				|| cur->content[var_len] == '\0'))
		{
			if (prev)
				prev->next = cur->next;
			else
				main->env = cur->next;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}
