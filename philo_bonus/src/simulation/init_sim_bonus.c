/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/22 14:35:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/* Initializes processes:
* - each process represents a philosopher
* - if there is more than 1 philosopher, initializes the watcher's thread
*/
bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = give_current_time() + (table->nbr_philo * 50);
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
			init_error(ERR_PHILO, table, true);
		if (table->philo[i].pid == 0)
		{
			if (pthread_create(&table->philo[i].watcher, NULL, &watcher, &table->philo[i]))
				return (init_error(ERR_PHILO, table, true));
			launch_routine(&table->philo[i]);
		}
		i++;
	}
	if (pthread_create(&table->limiter, NULL, &limiter, table))
		return (init_error(ERR_THREAD, table, true));
	return (true);
}

/* Joins threads and end the simulation:
* - joins all the philosophers' thread
* - joins the watcher's thread if it exists
* - destroys the mutexes
* - frees the allocated pointers
*/
void	stop_simulation(t_table *table)
{
	sem_wait(table->sim_sem);
	table->end_sim = true;
	sem_post(table->ate_enough);
	pthread_join(table->limiter, NULL);
	kill_philosophers(table);
	clean_table(table, true);
}
