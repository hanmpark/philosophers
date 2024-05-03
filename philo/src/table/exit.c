/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:39:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "errors.h"
#include "timer.h"

/**
 * @brief Destroys the mutexes used in the simulation.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
static void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i]->meal_lock);
		pthread_mutex_destroy(table->fork[i]);
	}
	pthread_mutex_destroy(&table->sim_lock);
	pthread_mutex_destroy(&table->print_lock);
}

/**
 * @brief Frees a dynamically allocated array.
 *
 * @param array A pointer to the array to be freed.
 */
static void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/**
 * @brief Cleans up the table structure used in the simulation.
 *
 * @param table A pointer to the t_table structure to be cleaned up.
 * @param mutex A boolean indicating whether to destroy the mutexes.
 */
void	clean_table(t_table *table, bool mutex)
{
	if (!table)
		return ;
	if (mutex)
		destroy_mutexes(table);
	if (table->fork != NULL)
		free_array((void**)table->fork);
	if (table->philo != NULL)
		free_array((void**)table->philo);
	free(table);
}

/**
 * @brief Handles an initialization error.
 *
 * @param msg A string containing the error message to be printed.
 * @param table A pointer to the t_table structure to be cleaned up.
 * @param mutex A boolean indicating whether to destroy the mutexes.
 *
 * @return Returns false to indicate that an error occurred.
 */
bool	init_error(char *msg, t_table *table, bool mutex)
{
	if (table)
		clean_table(table, mutex);
	while (*msg)
		write(2, &*msg++, sizeof(char));
	write(2, HELP, sizeof(HELP));
	return (false);
}
