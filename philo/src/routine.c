/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:20:16 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/02 15:34:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->id - 1]);
	pthread_mutex_lock(&philo->table->fork[philo->id % philo->table->number_of_philo]);
	philo->last_eat = actual_time();
	print_status(philo, EATING);
	wait_time(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->fork[philo->id % philo->table->number_of_philo]);
	philo->times_eat++;
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	wait_time(philo->table->time_to_sleep);
}

void	*philo_routine(t_philo	*philo)
{
	wait_start_time(philo->table->start_time);
	if (philo->id % 2 != 0)
	{
		print_status(philo, THINKING);
		usleep(10);
	}
	while (philo->table->end_sim == true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_status(philo, THINKING);
	}
}
