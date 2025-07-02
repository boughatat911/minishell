/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:13:51 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 18:13:59 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	c;

	if (!s)
		return (0);
	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*ft_strcpy(const char *str, char *dest)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)ft_malloc((sizeof(char) * (i + 1)), MALLOC);
	if (!dest)
		return (NULL);
	return (ft_strcpy(s1, dest));
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	(1) && (i = 0, j = 0);
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (s2 && !s1)
		return (ft_strdup(s2));
	str = (char *)ft_malloc((sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2) + 1)), MALLOC);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] && s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
