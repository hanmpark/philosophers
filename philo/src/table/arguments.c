/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:29:18 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:40:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"
#include <limits.h>

/**
 * @brief Converts a string to an integer.
 *
 * @param arg The string to be converted.
 *
 * @return Returns the converted integer. If the string contains non-digit
 * characters or represents a number greater than INT_MAX, returns -1.
 */
int	philo_atoi(char *arg)
{
	unsigned int	number;
	int				i;

	i = -1;
	number = 0;
	while (arg && arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		number = number * 10 + (arg[i] - '0');
	}
	if (number > INT_MAX)
		return (-1);
	return ((int)number);
}

/**
 * @brief Checks the validity of the command line arguments.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed to the
 * program.
 *
 * @return Returns true if the arguments are valid. If the number of arguments
 * is not between 5 and 6, or if any argument is not a valid integer, returns
 * false and prints an error message.
 */
bool	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (init_error(ERR_ARGS, NULL, false));
	i = 0;
	while (++i < argc)
		if (philo_atoi(argv[i]) == -1)
			return (init_error(ERR_FORMAT, NULL, false));
	return (true);
}
