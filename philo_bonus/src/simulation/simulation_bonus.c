/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:57 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:03:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/**
 * @brief Simulates a philosopher's actions.
 *
 * If there is more than one philosopher, creates a watcher thread for the
 * philosopher. Then, launches the philosopher's routine and exits the process.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns true if the philosopher's actions were successfully
 * simulated, and false otherwise.
 */
static bool	philosopher(t_philo *philo)
{
	if (philo->table->nbr_philo > 1)
		if (pthread_create(&philo->watcher, NULL, &watcher, philo))
			return (false);
	launch_routine(philo);
	exit(0);
	return (true);
}

/**
 * @brief Starts the simulation.
 *
 * Initializes the start time of the simulation and the last meal time of each
 * philosopher. Then, creates a process for each philosopher and a watcher
 * thread for each philosopher. If the number of meals is set, creates a
 * limiter thread.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if the simulation was successfully started, and false
 * otherwise.
 */
bool	start_simulation(t_table *table)
{
	int	i;

	table->tm_start = give_current_time();
	i = -1;
	while (++i < table->nbr_philo)
	{
		table->philo[i].last_meal = table->tm_start;
		table->philo[i].pid = fork();
		if (table->philo[i].pid == ERROR)
			return (init_error(ERR_PHILO, table, true));
		if (table->philo[i].pid == CHILD_PROCESS)
			if (!philosopher(&table->philo[i]))
				return (init_error(ERR_PHILO, table, true));
	}
	if (pthread_create(&table->limiter, NULL, &limiter, table))
		return (init_error(ERR_THREAD, table, true));
	return (true);
}

/**
 * @brief Ends the simulation.
 *
 * Waits for the simulation lock semaphore to be posted, sets the end_sim flag
 * to true, posts to the philo_full semaphore, joins the limiter thread, kills
 * the philosophers, cleans up the simulation table, and then exits the program.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
void	end_simulation(t_table *table)
{
	sem_wait(table->sim_lock);
	table->end_sim = true;
	sem_post(table->philo_full);
	pthread_join(table->limiter, NULL);
	kill_philosophers(table);
	clean_table(table, true);
	exit(0);
}
