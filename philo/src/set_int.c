/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:19:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/12 18:55:00 by hanmpark         ###   ########.fr       */
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

static long int	ft_atol(char *nbr)
{
	int			negative;
	long int	res;
	int			i;

	i = 0;
	negative = 1;
	while (is_space(nbr[i]) == true)
		i++;
	if (nbr[i] == '-')
	{
		negative = -1;
		i++;
	}
	else if (nbr[i] == '+')
		i++;
	res = 0;
	while (nbr[i] && is_digit(nbr[i]) == true)
	{
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * negative);
}

int	set_int(char *nbr)
{
	long int	integer;

	integer = ft_atol(nbr);
	if (integer > INT_MAX || integer < INT_MIN)
		return (-1);
	return ((int)integer);
}
