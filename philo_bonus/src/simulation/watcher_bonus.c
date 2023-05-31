/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:37:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 13:04:13 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

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

/* Watcher's thread:
* - supervise its own philosopher
* - checks tm_starve
* - if an end condition is encountered, set end_sim to true
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
			exit(EXIT_SUCCESS);
		usleep(1000);
	}
	return (NULL);
}
