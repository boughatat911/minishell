/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:07 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/25 16:27:55 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(t_shell *main, char *var_name)
{
	size_t	len;
	t_env	*tmp;

	len = ft_strlen(var_name);
	tmp = main->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var_name, len) == 0
			&& tmp->content[len] == '=')
			return (tmp->content + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

void	hundle_export_args(t_shell *main, char **cmd, int i)
{
	char	*equal_signe;
	char	*plus_equal;

	equal_signe = ft_strchr(cmd[i], '=');
	plus_equal = ft_strstr(cmd[i], "+=");
	if (plus_equal && plus_equal == equal_signe - 1)
		plus_equal_hundle_case(main, cmd[i]);
	else if (equal_signe)
		hundle_equal_case(main, cmd, i);
	else
		hundle_no_case(main, cmd, i);
}
