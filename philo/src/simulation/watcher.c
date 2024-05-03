/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:06 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:43:18 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

/**
 * @brief Checks if a philosopher is healthy (has not starved).
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns true if the philosopher is healthy. If the philosopher has
 * starved, sets the simulation state to end, prints the philosopher's status,
 * and returns false.
 */
static bool	healthy_philosopher(t_philo *philo)
{
	time_t	timestamp;

	timestamp = current_time();
	pthread_mutex_lock(&philo->meal_lock);
	if (timestamp - philo->last_meal >= philo->table->tm_starve)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		set_sim_state(philo->table, true);
		print_status(philo, true, DEAD);
		return (false);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (true);
}

/**
 * @brief Checks if a philosopher is full
 * (has eaten the required number of meals).
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns 1 if the philosopher is full, and 0 otherwise.
 */
static unsigned int	full_philosopher(t_philo *philo)
{
	unsigned int	is_full;

	is_full = 0;
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->times_ate >= philo->table->nbr_meals)
		is_full = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	return (is_full);
}

/**
 * @brief Checks the end conditions of the simulation.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if an end condition is encountered (a philosopher has
 * starved or all philosophers have eaten the required number of meals).
 * Returns false otherwise.
 */
static bool	end_condition(t_table *table)
{
	int	fulfilled_meals;
	int	i;

	i = -1;
	fulfilled_meals = 0;
	while (++i < table->nbr_philo)
	{
		if (!healthy_philosopher(table->philo[i]))
			return (true);
		if (table->nbr_meals > 0)
			fulfilled_meals += full_philosopher(table->philo[i]);
	}
	if (fulfilled_meals == table->nbr_philo)
	{
		set_sim_state(table, true);
		return (true);
	}
	return (false);
}

/**
 * @brief The watcher's thread function.
 *
 * Supervises the philosophers, checks if any philosopher has starved or if all
 * philosophers have eaten the required number of meals. If an end condition is
 * encountered, sets the simulation state to end.
 *
 * @param arg A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns NULL when the simulation ends.
 */
void	*watcher(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (!table->nbr_meals)
		return (NULL);
	wait_until_start(table->tm_start);
	while ("Philosophers are annoying")
	{
		if (end_condition(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
