/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:06 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 14:42:31 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static void	set_sim_bool(t_table *table, bool state)
{
	pthread_mutex_lock(&table->end_sim_lock);
	table->end_sim = state;
	pthread_mutex_unlock(&table->end_sim_lock);
}

static bool	healthy_philo(t_philo *philo)
{
	time_t	timestamp;

	timestamp = give_actual_time();
	if (timestamp - philo->last_meal >= philo->table->tm_starve)
	{
		set_sim_bool(philo->table, true);
		print_status(philo, true, DEAD);
		pthread_mutex_unlock(&philo->philo_lock);
		return (false);
	}
	return (true);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	unsigned int	fulfilled_meals;

	i = 0;
	fulfilled_meals = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_lock(&table->philo[i].philo_lock);
		if (healthy_philo(&table->philo[i]) == false)
			return (true);
		if (table->nbr_meals > 0 && \
			table->philo[i].times_ate >= table->nbr_meals)
			fulfilled_meals++;
		pthread_mutex_unlock(&table->philo[i].philo_lock);
		i++;
	}
	if (table->nbr_meals > 0 && fulfilled_meals == table->nbr_philo)
	{
		set_sim_bool(table, true);
		return (true);
	}
	return (false);
}

bool	end_simulation(t_table *table)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&table->end_sim_lock);
	if (table->end_sim == true)
		end = true;
	pthread_mutex_unlock(&table->end_sim_lock);
	return (end);
}

/* Watcher's thread:
* - waits for all other threads to be initialized
* - supervise philosophers
* - checks tm_starve
* - checks nbr_meals
* - if an end condition is encountered, set end_sim to true
*/
void	*watcher(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->nbr_meals == 0)
		return (NULL);
	wait_until_start(table->tm_start);
	while ("Philosophers are annoying")
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
