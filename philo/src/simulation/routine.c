/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:58:53 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:49:35 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

/**
 * @brief Locks the forks for a philosopher.
 *
 * Locks the forks for a philosopher based on their ID.
 * If the philosopher is the last one, the order of locking is reversed.
 *
 * @param ph A pointer to the t_philo structure representing the philosopher.
 */
static void	lock_forks(t_philo *ph)
{
	if (ph->id == ph->table->nbr_philo)
	{
		pthread_mutex_lock(ph->table->fork[ph->id % ph->table->nbr_philo]);
		pthread_mutex_lock(ph->table->fork[ph->id - 1]);
	}
	else
	{
		pthread_mutex_lock(ph->table->fork[ph->id - 1]);
		pthread_mutex_lock(ph->table->fork[ph->id % ph->table->nbr_philo]);
	}
	print_status(ph, false, FORK);
	print_status(ph, false, FORK);
}

/**
 * @brief Simulates a philosopher eating.
 *
 * Locks the forks, updates the time of the last meal and the number of times
 * the philosopher has eaten, waits for the time it takes to eat, and then
 * unlocks the forks.
 *
 * @param ph A pointer to the t_philo structure representing the philosopher.
 */
static void	eat(t_philo *ph)
{
	lock_forks(ph);
	print_status(ph, false, EAT);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = current_time();
	ph->times_ate++;
	pthread_mutex_unlock(&ph->meal_lock);
	philo_wait(ph->table, EAT);
	pthread_mutex_unlock(ph->table->fork[ph->id - 1]);
	pthread_mutex_unlock(ph->table->fork[ph->id % ph->table->nbr_philo]);
}

/**
 * @brief Simulates a philosopher's routine (eating, sleeping, and thinking).
 *
 * @param ph A pointer to the t_philo structure representing the philosopher.
 */
static void	routine(t_philo *ph)
{
	eat(ph);
	print_status(ph, false, SLEEP);
	philo_wait(ph->table, SLEEP);
	print_status(ph, false, THINK);
}

/**
 * @brief Simulates a philosopher's routine when there is only one philosopher.
 *
 * Locks the fork, waits until the philosopher starves, and then unlocks the
 * fork.
 *
 * @param ph A pointer to the t_philo structure representing the philosopher.
 */
static void	lonely_routine(t_philo *ph)
{
	pthread_mutex_lock(ph->table->fork[0]);
	print_status(ph, false, FORK);
	philo_wait(ph->table, DEAD);
	print_status(ph, true, DEAD);
	ph->table->end_sim = true;
	pthread_mutex_unlock(ph->table->fork[0]);
}

/**
 * @brief Launches a philosopher's routine.
 *
 * If there is only one philosopher, launches the lonely_routine(). Otherwise,
 * launches the basic routine (eat, sleep, and think).
 *
 * @param arg A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns NULL when the routine ends.
 */
void	*launch_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo->table->nbr_meals || !philo->table->tm_starve)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = philo->table->tm_start;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_until_start(philo->table->tm_start);
	if (check_sim_state(philo->table))
		return (NULL);
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2)
	{
		print_status(philo, false, THINK);
		usleep(10000);
	}
	while (!check_sim_state(philo->table))
		routine(philo);
	return (NULL);
}
