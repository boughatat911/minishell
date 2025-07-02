/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:13:18 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 13:17:37 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_special_char2(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$');
}

char	*strjoin_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = ft_malloc(len + 2, MALLOC);
	if (str)
		ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	(1) && (i = 0, j = 0, res = ft_malloc(ft_strlen(str) + 1, MALLOC));
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"')
			res[j++] = str[i++];
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else
			return (res[j] = '\0', res);
		while (str[i] && str[i] != quote)
			res[j++] = str[i++];
		if (str[i])
			i++;
		while (str[i] && !is_special_char(str[i]))
			res[j++] = str[i++];
	}
	return (res[j] = '\0', res);
}

int	gg(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*up_re_case(t_token *tok, char *str)
{
	if (!gg(str))
		tok->index = -13;
	return (remove_quotes(str));
}
