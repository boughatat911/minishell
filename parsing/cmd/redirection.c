/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:06:13 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 16:50:29 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	if (start->content && ft_strchr(start->content, ' '))
	{
		close(node->in);
		node->in = -1;
		node->fd_statuts = 1;
		write(2, "ambiguous redirect\n", 19);
		ft_exit_status(1, 1);
		return ((start)->next);
	}
	fd = open(start->content, O_RDONLY);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		ft_exit_status(1, 1);
		perror(start->content);
		return (start->next);
	}
	ft_cls(node->in);
	node->in = fd;
	ft_exit_status(0, 1);
	return (start->next);
}

t_token	*handle_redir_out(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	if (start && start->index == -13)
	{
		write(2, "No such file or directory\n", 27);
		ft_exit_status(1, 1);
		return ((start)->next);
	}
	if (!start ||!start->content[0])
	{
		node->out = -1;
		node->fd_statuts = 1;
		write(2, "ambiguous redirect\n", 19);
		return (ft_exit_status(1, 1), (start)->next);
	}
	fd = open(start->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		return (ft_exit_status(1, 1), perror(start->content), start->next);
	}
	(1) && (ft_cls(node->out), node->out = fd, ft_exit_status(0, 1));
	return (start->next);
}

t_token	*handle_redir_append(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		ft_exit_status(1, 1);
		perror(start->content);
		return (start->next);
	}
	ft_cls(node->out);
	node->out = fd;
	ft_exit_status(0, 1);
	return (start->next);
}

void	ft_skipe_delimiter(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			tmp->next->type = DILIMITER;
		tmp = tmp->next;
	}	
}
