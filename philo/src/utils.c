/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:19:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/11 16:33:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || \
		c == '\v');
}

int	ft_atoi(char *str)
{
	int	negative;
	int	res;
	int	i;

	i = 0;
	negative = 1;
	while (is_space(str[i]) == true)
		i++;
	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = 0;
	while (str[i] && is_digit(str[i]) == true)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * negative);
}

void	ft_error(const char *message)
{
	perror(message);
	exit(1);
}