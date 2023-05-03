/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:20:16 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/03 16:33:50 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->id - 1]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->table->fork[philo->id % philo->table->number_of_philo]);
	print_status(philo, FORK);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = actual_time();
	if (sim_has_ended(philo) == false)
		philo->times_eat++;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_time(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->fork[philo->id % philo->table->number_of_philo]);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	wait_time(philo->table->time_to_sleep);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_start_time(philo->table->start_time);
	if (philo->id % 2 != 0)
	{
		print_status(philo, THINKING);
		wait_time(200);
	}
	while (sim_has_ended(philo) == false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_status(philo, THINKING);
	}
	return (NULL);
}
