/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:35:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 15:09:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"
#include "timer.h"

/* Initializes threads:
* - each thread represents a philosopher
* - if there is more than 1 philosopher, initialize the watcher's thread
*/
bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = give_actual_time() + (table->nbr_philo * 20);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &launch_routine, \
			&table->philo[i]) != 0)
			return (bool_error(ERR_THREAD, table->fork, table->philo));
		i++;
	}
	if (table->nbr_philo > 1)
		if (pthread_create(&table->watcher, NULL, &watcher, table) != 0)
			return (bool_error(ERR_THREAD, table->fork, table->philo));
	return (true);
}

/* Joins threads and end the simulation:
* - joins all the philosophers' thread
* - joins the watcher's thread if it exists
* - destroys the mutexes
* - frees the allocated pointers
*/
bool	stop_simulation(t_table *table)
{
	unsigned int	i;
	bool			clear_end;

	i = 0;
	clear_end = true;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			clear_end = false;
		i++;
	}
	if (table->nbr_philo > 1)
		if (pthread_join(table->watcher, NULL) != 0)
			clear_end = false;
	clean_table(table, true);
	if (clear_end == false)
		return (bool_error(ERR_JOIN, NULL, NULL));
	return (clear_end);
}
