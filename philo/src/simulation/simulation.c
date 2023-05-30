/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:35:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 17:03:44 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"
#include "status.h"
#include "timer.h"

/* Initializes threads:
* - each thread represents a philosopher
* - if there is more than 1 philosopher, initializes the watcher's thread
*/
bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = current_time();
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &launch_routine, \
			&table->philo[i]))
			return (init_error(ERR_THREAD, table, true));
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &watcher, table))
		return (init_error(ERR_THREAD, table, true));
	return (true);
}

/* Joins threads and end the simulation:
* - joins all the philosophers' thread
* - joins the watcher's thread if it exists
* - destroys the mutexes
* - frees the allocated pointers
*/
void	end_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	pthread_join(table->watcher, NULL);
	clean_table(table, true);
}
