/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:20:33 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/28 17:52:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_is_digit(char *str)
{
	int					i;
	int					s;
	unsigned long long	n;

	(1) && (i = 0, s = 1, n = 0);
	if (!str[i])
		return (0);
	(str[i] == '-') && (s = -1);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		n = (n * 10) + (str[i] - '0');
		if (n > 9223372036854775807ULL && s > 0)
			return (0);
		else if (n > 9223372036854775808ULL && s < 0)
			return (0);
		i++;
	}
	return (1);
}

int	len_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long long	ft_atoll(char *str)
{
	int			signe;
	long long	result_tmp;
	long long	result;

	signe = 1;
	result = 0;
	result_tmp = 0;
	while (*str == 32 || (*str < 14 && *str > 8))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result_tmp * 10 + (*str++ - 48);
		if (result < result_tmp && signe == 1)
			return (-1);
		if (result < result_tmp && signe == -1)
			return (0);
		result_tmp = result;
	}
	return (result * signe);
}

int	my_exit(char **cmd)
{
	int		ac;
	long	exit_st;

	ac = len_2d(cmd);
	exit_st = 0;
	if (ac == 1)
	{	
		printf("exit\n");
		ft_malloc(0, FREE);
		exit(ft_exit_status(0, 1));
	}	
	if (!str_is_digit(cmd[1]))
	{
		printf("exit\n");
		ft_putstr_fd("numeric argument required\n", 2);
		exit(ft_exit_status(2, 1));
	}
	if (ac > 2)
	{
		printf("exit\n");
		(ft_putstr_fd("too many arguments\n", 2), ft_exit_status(1, 1));
		return (1);
	}
	exit_st = ft_atoll(cmd[1]);
	exit((unsigned char)exit_st);
}
