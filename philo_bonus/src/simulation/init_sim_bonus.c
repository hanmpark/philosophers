/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/20 16:23:25 by hanmpark         ###   ########.fr       */
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

	table->tm_start = give_current_time() + (table->nbr_philo * 30);
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
			init_error(ERR_PHILO, table, true);
		if (table->philo[i].pid == 0)
			launch_routine(&table->philo[i]);
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
	unsigned int	i;

	i = 0;
	while (table->nbr_philo > 1 && i < table->nbr_philo)
	{
		pthread_join(table->philo[i].hunger_watcher, NULL);
		i++;
	}
	pthread_join(table->limiter, NULL);
	sem_wait(table->sim_sem);
	table->end_sim = true;
	kill_philosophers(table);
	clean_table(table, true);
}
