/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:37:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/23 12:59:05 by hanmpark         ###   ########.fr       */
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
		sem_post(philo->table->sim_sem);
		print_status(philo, true, DEAD);
		return (false);
	}
	sem_post(philo->meal_lock);
	return (true);
}

static void	full_philosopher(t_philo *philo)
{
	sem_wait(philo->count_lock);
	if (philo->count_meal == philo->table->nbr_meals)
		sem_post(philo->table->ate_enough);
	sem_post(philo->count_lock);
}

/* Watcher's thread:
* - waits for all other processes
* - supervise philosophers
* - checks tm_starve
* - checks nbr_meals
* - if an end condition is encountered, set end_sim to true
*/
void	*watcher(void *data)
{
	t_philo	*philo;
	bool	passed;

	philo = (t_philo *)data;
	if (philo->table->nbr_philo < 2 || philo->table->nbr_meals == 0)
		return (NULL);
	passed = false;
	wait_until_start(philo->table->tm_start);
	while ("Philosophers are annoying")
	{
		if (healthy_philosopher(philo) == false)
			return (NULL);
		if (philo->table->nbr_meals > 0)
			full_philosopher(philo);
		usleep(1000);
	}
	return (NULL);
}
