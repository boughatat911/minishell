/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 13:36:32 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*tok;

	tok = ft_malloc(sizeof(t_token), MALLOC);
	tok->content = content;
	tok->ex_space_flag = 0;
	tok->flag = 0;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **lst, char *content, t_token_type type, int index)
{
	t_token	*tok;
	t_token	*tmp;

	tok = new_token(content, type);
	tok->index = index;
	if (!*lst)
		*lst = tok;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
	}
}

char	*substr(char *s, int start, int len)
{
	char	*out;

	out = ft_malloc((len + 1), MALLOC);
	ft_strncpy(out, s + start, len);
	out[len] = 0;
	return (out);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	final = ft_lstlast(*lst);
	final->next = new;
	return ;
}

char	add_token_list(char *input, int *i, char quote_char)
{
	quote_char = input[(*i)++];
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i])
		(*i)++;
	quote_char = 0;
	return (quote_char);
}
