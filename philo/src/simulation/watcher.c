/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:06 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 17:20:34 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

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

static bool	end_condition(t_table *table)
{
	unsigned int	i;
	unsigned int	fulfilled_meals;

	i = 0;
	fulfilled_meals = 0;
	while (i < table->nbr_philo)
	{
		if (!healthy_philosopher(&table->philo[i]))
			return (true);
		if (table->nbr_meals > 0)
			fulfilled_meals += full_philosopher(&table->philo[i]);
		i++;
	}
	if (fulfilled_meals == table->nbr_philo)
	{
		set_sim_state(table, true);
		return (true);
	}
	return (false);
}

/* Watcher's thread:
* - supervise philosophers
* - checks tm_starve
* - checks nbr_meals
* - if an end condition is encountered, set end_sim to true
*/
void	*watcher(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (!table->nbr_meals)
		return (NULL);
	while ("Philosophers are annoying")
	{
		if (end_condition(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
