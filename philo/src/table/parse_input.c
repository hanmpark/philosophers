/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:15:26 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:47:03 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "table_tools.h"

// Checks if the argument is strictly composed of digits
static bool	check_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

// Basically an atoi() that returns -1 if the argument is not an integer
int	philo_atoi(char *arg)
{
	unsigned long int	nbr;
	int					i;

	i = 0;
	nbr = 0;
	while (arg && arg[i] && (arg[i] >= '0' && arg[i] <= '9'))
	{
		nbr = nbr * 10 + (arg[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return ((int)nbr);
}

// Checks if the arguments are valid inputs
bool	valid_input(int argc, char **argv)
{
	int	i;
	int	nbr;

	i = 1;
	while (i < argc)
	{
		if (check_digit(argv[i]) == false)
			return (false);
		nbr = philo_atoi(argv[i]);
		if ((i == 1 && nbr <= 0) || (i > 1 && nbr == -1))
			return (false);
		i++;
	}
	return (true);
}
