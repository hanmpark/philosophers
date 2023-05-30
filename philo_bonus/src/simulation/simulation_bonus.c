/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 17:57:31 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

static bool	philosopher(t_philo *philo)
{
	if (philo->table->nbr_philo > 1)
		if (pthread_create(&philo->watcher, NULL, &watcher, philo))
			return (false);
	launch_routine(philo);
	exit(EXIT_SUCCESS);
}

/* Initializes processes:
* - each process represents a philosopher
* - if there is more than 1 philosopher, initializes the watcher's thread
*/
bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = give_current_time();
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].last_meal = table->tm_start;
		table->philo[i].pid = fork();
		if (table->philo[i].pid == ERROR)
			return (init_error(ERR_PHILO, table, true));
		if (table->philo[i].pid == CHILD_PROCESS)
			if (!philosopher(&table->philo[i]))
				return (init_error(ERR_PHILO, table, true));
		i++;
	}
	if (pthread_create(&table->limiter, NULL, &limiter, table))
		return (init_error(ERR_THREAD, table, true));
	return (true);
}

/* End the simulation:
* - waits for the sem_post(table->sim_lock)
* - joins the limiter's thread
* - destroys the semaphores
* - frees the allocated pointers
*/
void	end_simulation(t_table *table)
{
	sem_wait(table->sim_lock);
	table->end_sim = true;
	sem_post(table->ate_enough);
	pthread_join(table->limiter, NULL);
	kill_philosophers(table);
	clean_table(table, true);
	exit(EXIT_SUCCESS);
}
