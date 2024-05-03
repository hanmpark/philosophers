/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:37:55 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:01:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/**
 * @brief Checks if a philosopher is healthy.
 *
 * Gets the current time and checks if the time since the philosopher's last
 * meal is greater than or equal to the time before a philosopher starves. If
 * it is, prints the philosopher's status as DEAD, posts to the simulation lock
 * semaphore, and returns false. Otherwise, returns true.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns true if the philosopher is healthy, and false otherwise.
 */
static bool	healthy_philosopher(t_philo *philo)
{
	time_t	timestamp;

	timestamp = give_current_time();
	sem_wait(philo->meal_lock);
	if (timestamp - philo->last_meal >= philo->table->tm_starve)
	{
		sem_post(philo->meal_lock);
		print_status(philo, true, DEAD);
		sem_post(philo->table->sim_lock);
		return (false);
	}
	sem_post(philo->meal_lock);
	return (true);
}

/**
 * @brief Supervises a philosopher.
 *
 * Checks if the number of meals or the time before a philosopher starves is
 * zero. If either is zero, returns NULL. Otherwise, continuously checks if the
 * philosopher is healthy. If the philosopher is not healthy, exits the
 * program. Sleeps for 1 millisecond between each check.
 *
 * @param data A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns NULL.
 */
void	*watcher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!philo->table->nbr_meals || !philo->table->tm_starve)
		return (NULL);
	while ("Philosophers are annoying")
	{
		if (!healthy_philosopher(philo))
			exit(0);
		usleep(1000);
	}
	return (NULL);
}
