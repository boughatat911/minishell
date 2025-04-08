#include "parser.h"

static t_redir	*create_redir(char *file, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = file;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

static void	add_redir(t_redir **redirs, t_redir *new)
{
	t_redir	*current;

	if (!*redirs)
		*redirs = new;
	else
	{
		current = *redirs;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

static void	add_arg(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

static void	handle_redirection(t_cmd *cmd, t_token *token, t_token *next)
{
	t_redir	*redir;
	int		type;

	if (token->type == T_REDIR_IN)
		type = 0;
	else if (token->type == T_REDIR_OUT)
		type = 1;
	else
		type = 2;
	redir = create_redir(ft_strdup(next->value), type);
	if (!redir)
		return;
	add_redir(&cmd->redirs, redir);
}

static t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	current = *tokens;
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_WORD)
			add_arg(cmd, ft_strdup(current->value));
		else if (current->type == T_REDIR_IN || current->type == T_REDIR_OUT ||
				current->type == T_REDIR_APPEND)
		{
			if (!current->next || current->next->type != T_WORD)
			{
				free_cmd_list(cmd);
				return (NULL);
			}
			handle_redirection(cmd, current, current->next);
			current = current->next;
		}
		current = current->next;
	}
	*tokens = current;
	return (cmd);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new;

	head = NULL;
	while (tokens)
	{
		new = parse_command(&tokens);
		if (!new)
		{
			free_cmd_list(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
		{
			current = head;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		if (tmp->redirs)
			free_redirs(tmp->redirs);
		if (tmp->in_fd != STDIN_FILENO)
			close(tmp->in_fd);
		if (tmp->out_fd != STDOUT_FILENO)
			close(tmp->out_fd);
		free(tmp);
	}
} 