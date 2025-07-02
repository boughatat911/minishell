/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/29 15:10:08 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*store_cmd_node(t_cmd *node_to_fill, t_token *start)
{
	if (!start)
		return (NULL);
	while (start && start->type != PIPE)
	{
		start = handle_token_type(node_to_fill, start);
		if (node_to_fill->fd_statuts == 1)
		{
			while (start && start->type != PIPE)
				start = start->next;
			break ;
		}
	}
	return (start);
}

t_token	*handle_token_type(t_cmd *node, t_token *start)
{
	if (start->type == WORD)
	{
		if (start->content && start->flag == 0)
		{
			if (start->content[0])
				node->cmd = ft_strjoin2d(node->cmd, start->content);
			else
			{
				if (ft_g1(node->cmd))
					node->cmd = ft_strjoin2d(node->cmd, ft_strdup("\"\""));
				else
					node->cmd = ft_strjoin2d(node->cmd, start->content);
			}
		}
		else if (start->content && start->content[0])
			node->cmd = ft_strjoin2d(node->cmd, start->content);
		return (start->next);
	}
	else if (start->type == REDIR_IN)
		return (handle_redir_in(node, start));
	else if (start->type == REDIR_OUT)
		return (handle_redir_out(node, start));
	else if (start->type == APPEND)
		return (handle_redir_append(node, start));
	return (start->next);
}

t_token	*handle_heredoc_token(t_shell *shell, t_cmd *node, t_token *start)
{
	int		fd[2];
	char	*filepath;

	filepath = malloc(0);
	free(filepath);
	start = start->next;
	filepath = ft_strjoin("/tmp/", ft_itoa((size_t)filepath % 10000));
	fd[0] = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd[1] = open(filepath, O_RDONLY);
	if (unlink(filepath) == -1 || fd[0] == -1 || fd[1] == -1)
	{
		(ft_cls(fd[0]), ft_cls(fd[1]));
		node->fd_statuts = 1;
		ft_exit_status(1, 1);
		perror(start->content);
		return (start->next);
	}
	handle_heredoc(shell, start->content, fd[0], node);
	ft_cls(node->in);
	node->in = fd[1];
	if (node->heredoc_statuts == 911)
		return (start->next);
	ft_exit_status(0, 1);
	return (start->next);
}

t_token	*heredoc_while(t_shell *shell, t_cmd *node_to_fill, t_token *start)
{
	if (!start)
		return (NULL);
	while (start && start->type != PIPE)
	{
		if (start->type == HEREDOC)
		{
			start = handle_heredoc_token(shell, node_to_fill, start);
			if (node_to_fill->heredoc_statuts == 911)
				return (start);
		}
		else
			start = start->next;
	}
	return (start);
}

t_cmd	*ft_cmd(t_shell *shell, t_token **token)
{
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*cmd_tmp;

	tmp = *token;
	cmd_tmp = ft_lstnew_cmd();
	head = cmd_tmp;
	while (tmp)
	{
		tmp = heredoc_while(shell, cmd_tmp, tmp);
		if (cmd_tmp->heredoc_statuts == 911)
			return (head);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = ft_lstnew_cmd();
			ft_lstadd_back_cmd(&head, cmd_tmp);
			tmp = tmp->next;
		}
	}
	cmd_tmp = head;
	tmp = *token;
	ft_cmd_2(tmp, cmd_tmp);
	ft_redirections(head);
	return (head);
}
