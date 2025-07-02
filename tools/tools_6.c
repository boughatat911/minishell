/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:14:41 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 18:14:42 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '"' || c == '\'' || c == ' ');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src && n == 0)
		return (NULL);
	if (!dst || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

int	ft_count_heredoc(t_token *tok)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			i++;
		tmp = tmp->next;
	}
	if (i >= 17)
		return (1);
	return (0);
}

int	ft_cls(int fd)
{
	if (fd == -1337)
		return (1);
	return (close(fd));
}
