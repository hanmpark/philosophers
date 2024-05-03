/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:35:33 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:47:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"
#include "status.h"
#include "timer.h"

/**
 * @brief Initializes threads for the simulation.
 *
 * Each thread represents a philosopher. Also initializes the watcher's thread
 * if there is more than one philosopher.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if the threads were successfully initialized. If there
 * was an error during thread creation, returns false and prints an error
 * message.
 */
bool	start_simulation(t_table *table)
{
	int	i;

	table->tm_start = current_time() + (table->nbr_philo * 20);
	i = -1;
	while (++i < table->nbr_philo)
		if (pthread_create(&table->philo[i]->thread, NULL, &launch_routine, \
			table->philo[i]))
			return (init_error(ERR_THREAD, table, true));
	if (table->nbr_philo > 1)
		if (pthread_create(&table->watcher, NULL, &watcher, table))
			return (init_error(ERR_THREAD, table, true));
	return (true);
}

/**
 * @brief Joins threads and ends the simulation.
 *
 * Joins all the philosophers' threads and the watcher's thread if it exists.
 * Destroys the mutexes and frees the allocated pointers.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
void	end_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
		pthread_join(table->philo[i]->thread, NULL);
	if (table->nbr_philo > 1)
		pthread_join(table->watcher, NULL);
	clean_table(table, true);
}
