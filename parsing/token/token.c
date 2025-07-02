/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/26 16:26:15 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_str(t_token **tokens, char *input, int *i, int *index)
{
	int		start;
	char	quote_char;

	start = *i;
	quote_char = 0;
	while (input[*i] && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if ((input[*i] == '\'' || input[*i] == '\"'))
		{
			if (quote_char == 0)
				quote_char = add_token_list(input, i, quote_char);
		}
		else if (input[*i] == ' ' && quote_char == 0)
			break ;
		else
			(*i)++;
	}
	if (*i > start)
		add_token(tokens, substr(input, start, (*i) - start), WORD, (*index)++);
	while (input[*i] == ' ' && quote_char == 0)
		(*i)++;
}

void	lexer_2(t_token **tokens, char *input, int *i, int *index)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, ft_strdup("<<"), HEREDOC, *index);
		(1) && ((*i) += 2, (*index)++);
	}
	else if (input[*i] == '>')
	{
		add_token(tokens, ft_strdup(">"), REDIR_OUT, (*index));
		(1) && ((*i)++, (*index)++);
	}
	else if (input[(*i)] == '|')
	{
		add_token(tokens, ft_strdup("|"), PIPE, (*index));
		(1) && ((*i)++, (*index)++);
	}
	else if (input[*i] == '<')
	{
		add_token(tokens, ft_strdup("<"), REDIR_IN, (*index));
		(1) && ((*i)++, index++);
	}
	else if (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>' )
		token_str(tokens, input, i, index);
}

int	lexer_1(char *input, t_token **tokens)
{
	int	i;
	int	index;

	i = 0;
	index = 1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, ft_strdup(">>"), APPEND, index);
			(1) && (i += 2, index++);
		}
		else
			lexer_2(tokens, input, &i, &index);
	}
	return (1);
}
