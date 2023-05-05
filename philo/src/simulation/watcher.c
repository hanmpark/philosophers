/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:45:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:49:43 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "print_status.h"

// Sets the end_sim boolean
static void	set_sim_bool(t_table *table, bool state)
{
	pthread_mutex_lock(&table->end_sim_lock);
	table->end_sim = state;
	pthread_mutex_unlock(&table->end_sim_lock);
}

// Checks wether the philosopher is dead or alive
static bool	healthy_philo(t_philo *philo)
{
	time_t	timestamp;

	timestamp = actual_time();
	if (timestamp - philo->last_eat >= philo->table->time_to_die)
	{
		set_sim_bool(philo->table, true);
		print_status(philo, true, DEAD);
		pthread_mutex_unlock(&philo->meal_lock);
		return (false);
	}
	return (true);
}

// Checks if the simulation has reached an end condition
static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	unsigned int	fulfilled_meals_philo;

	i = 0;
	fulfilled_meals_philo = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_lock(&table->philo[i].meal_lock);
		if (healthy_philo(&table->philo[i]) == false)
			return (true);
		if (table->number_of_meals > 0 && \
			table->philo[i].times_eat >= table->number_of_meals)
			fulfilled_meals_philo++;
		pthread_mutex_unlock(&table->philo[i].meal_lock);
		i++;
	}
	if (table->number_of_meals > 0 && \
		fulfilled_meals_philo == table->number_of_philo)
	{
		set_sim_bool(table, true);
		return (true);
	}
	return (false);
}

// Checks the simulation's state when there is more than 1 philosopher
void	*watcher(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->number_of_meals == 0 || table->number_of_philo < 1)
		return (NULL);
	set_sim_bool(table, false);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
