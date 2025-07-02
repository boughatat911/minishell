/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:51 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/29 15:23:24 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_malloc	*new_node(void	*ptr)
{
	t_malloc	*new;

	new = malloc(sizeof(t_malloc));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

t_malloc	*last_node(t_malloc **head)
{
	t_malloc	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_malloc	**head, t_malloc *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
		last_node(head)->next = new;
}

void	clear_all(t_malloc **head)
{
	t_malloc	*cur;
	t_malloc	*tmp;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->ptr);
		cur->ptr = NULL;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, t_call call)
{
	static t_malloc	*head;
	t_malloc		*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
		{
			clear_all(&head);
			exit(ft_exit_status(1, 1));
		}
		tmp = new_node(ptr);
		if (!tmp)
			(clear_all(&head), free(ptr), exit(ft_exit_status(1, 1)));
		add_back(&head, tmp);
		ft_bzero(ptr, size);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}
