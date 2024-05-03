/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:29:18 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:00:33 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include <limits.h>

/**
 * @brief Converts a string to an integer.
 *
 * Converts a string to an integer, checking that each character is a digit. If
 * the string contains a non-digit character or the integer is greater than
 * INT_MAX, returns -1.
 *
 * @param arg The string to convert to an integer.
 *
 * @return Returns the integer representation of the string, or -1 if the string
 * contains a non-digit character or the integer is greater than INT_MAX.
 */
int	philo_atoi(char *arg)
{
	unsigned int	number;
	unsigned int	i;

	i = 0;
	number = 0;
	while (arg && arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		number = number * 10 + (arg[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return (number);
}

/**
 * @brief Checks the arguments passed to the program.
 *
 * Checks that the number of arguments is between 5 and 6, and that each
 * argument is a positive integer. If these conditions are not met, calls the
 * init_error function to handle the error and returns false.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed to the
 * program.
 *
 * @return Returns true if the arguments are valid, and false otherwise.
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
