/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:51:20 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 17:07:05 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "table_tools.h"

/* Launches the simulation:
* - sets the simulation's start time
* - creates threads representing philosophers
* - if there is more than 1 philosopher, creates the watcher's thread
*/
bool	start_sim(t_table *table)
{
	unsigned int	i;

	if (table->number_of_philo == 1)
	{
		if (pthread_create(&table->philo[0].thread, NULL, &lonely_routine, \
			&table->philo[0]) != 0)
			return (false);
		return (true);
	}
	i = 0;
	table->start_time = actual_time();
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &launch_routine, \
			&table->philo[i]) != 0)
			return (false);
		usleep(20);
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &watcher, table) != 0)
		return (false);
	return (true);
}

// Stops the simulation cleaning every thread created, mutexes and allocations
void	stop_sim(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	if (table->number_of_philo > 1)
		pthread_join(table->watcher, NULL);
	clean_table(table);
}
