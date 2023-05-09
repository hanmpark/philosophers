/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:29:18 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 14:47:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>

int	philo_atoi(char *arg)
{
	unsigned int	number;
	unsigned int	i;

	i = 0;
	number = 0;
	while (arg && arg[i])
	{
		if (arg[i] < '0' && arg[i] > '9')
			return (-1);
		number = number * 10 + (arg[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return ((int)number);
}

bool	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (bool_error(ERR_ARGS, NULL, NULL));
	i = 1;
	while (i < argc)
	{
		if (philo_atoi(argv[i]) == -1)
			return (bool_error(ERR_FORMAT, NULL, NULL));
		i++;
	}
	return (true);
}
