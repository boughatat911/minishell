/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:14:33 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 18:14:34 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_count_2d(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_strjoin2d(char **s1, char *s2)
{
	size_t	len1;
	size_t	i;
	char	**new;

	len1 = ft_count_2d(s1);
	i = 0;
	if (!s1 && s2)
		return (new = ft_malloc(2 * sizeof(char *),
				MALLOC), new[0] = ft_strdup(s2), new[1] = NULL, new);
	if (s1 && !s2)
		return (s1);
	new = ft_malloc(sizeof(char *) * (len1 + 2), MALLOC);
	while (i < len1)
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	new[i++] = ft_strdup(s2);
	new[i] = NULL;
	return (new);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	len_n(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = len_n(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = ft_malloc(sizeof(char) * (len + 1), MALLOC);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
