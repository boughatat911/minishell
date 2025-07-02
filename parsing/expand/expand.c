/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/28 14:37:28 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_single_quot(char *str, int *i, char *res)
{
	res = strjoin_char(res, str[(*i)++]);
	res = strjoin_char(res, str[(*i)++]);
	while (str[*i] && str[*i] != '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*handle_regular_quotes(char *str, int *i, char *res, char *quot)
{
	if ((str[*i] == '\'' || str[*i] == '"') && *quot == 0)
	{
		*quot = str[*i];
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	else if (str[*i] == *quot)
	{
		*quot = 0;
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*handle_var_expand(char *str, int *i, t_shell *shell, char *res)
{
	if (str[*i] == '$' && str[*i + 1] == '$')
		*i += 2;
	else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
	{
		*i += 2;
		res = ft_strjoin(res, ft_itoa(ft_exit_status(0, 0)));
	}
	else if (str[*i] == '$' && str[*i + 1] && ft_isalpha(str[*i + 1])
		&& !ft_quote(str[*i + 1]))
	{
		res = expand_env_var(str, i, shell->env, res);
	}
	else if (str[*i] == '$' && str[*i + 1] && !ft_isalpha(str[*i + 1])
		&& !ft_quote(str[*i + 1]))
		(*i) += 2;
	else
		res = strjoin_char(res, str[(*i)++]);
	return (res);
}

char	*ft_expand_token(char *str, t_shell *shell, t_token *tok)
{
	int		i;
	char	*res;
	char	quot;

	tok->flag = 1;
	i = 0;
	quot = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\'')
			res = join_single_quot(str, &i, res);
		else
		{
			res = handle_regular_quotes(str, &i, res, &quot);
			if (str[i])
				res = handle_var_expand(str, &i, shell, res);
		}
	}
	return (ft_dolar(res));
}

void	ft_expand(t_shell *shell)
{
	t_token		*tok;
	char		*expanded;
	char		*tmp;

	tok = token_up(shell->token);
	while (tok)
	{
		if (tok->type == WORD)
		{
			if (ft_strchr(tok->content, '$'))
				expanded = ft_expand_token(tok->content, shell, tok);
			else
				expanded = tok->content;
			tmp = remove_quotes(expanded);
			if (tmp && !tmp[0] && shell->env->quot == 1)
				(1) && (tok->content = expanded);
			else if (!ft_strchr(tok->content, '$'))
				tok->content = up_re_case(tok, tok->content);
			else if (!ft_strchr(expanded, ' '))
				tok->content = up_re_case(tok, expanded);
			else
				tok = split_to_token_list(tok, ft_split_space(expanded));
		}
		tok = tok->next;
	}
}
