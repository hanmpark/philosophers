/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:58:53 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 15:43:28 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*print_status(t_philo *philo, bool last, t_status status)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->table->print);
	if (end_simulation(philo->table) == true && last == false)
	{
		pthread_mutex_unlock(&philo->table->print);
		return (NULL);
	}
	timestamp = give_actual_time() - philo->table->tm_start;
	if (status == DEAD)
		printf("%ld %d died\n", timestamp, philo->id);
	if (status == FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->id);
	if (status == EAT)
		printf("%ld %d is eating\n", timestamp, philo->id);
	if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, philo->id);
	if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->id - 1]);
	print_status(philo, false, FORK);
	pthread_mutex_lock(&philo->table->fork[philo->id % philo->table->nbr_philo]);
	print_status(philo, false, FORK);
	print_status(philo, false, EAT);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = give_actual_time();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->philo_lock);
	philo_wait(philo->table, EAT);
}

static void	routine(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_unlock(&philo->table->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->fork[philo->id % philo->table->nbr_philo]);
	print_status(philo, false, SLEEP);
	philo_wait(philo->table, SLEEP);
	print_status(philo, false, THINK);
}

static void	lonely_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[0]);
	print_status(philo, false, FORK);
	philo_wait(philo->table, philo->table->tm_starve);
	pthread_mutex_lock(&philo->table->end_sim_lock);
	philo->table->end_sim = true;
	pthread_mutex_unlock(&philo->table->end_sim_lock);
	print_status(philo, true, DEAD);
	pthread_mutex_unlock(&philo->table->fork[0]);
}

void	*launch_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->nbr_meals == 0 || philo->table->tm_starve == 0)
		return (NULL);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = philo->table->tm_start;
	pthread_mutex_unlock(&philo->philo_lock);
	wait_until_start(philo->table->tm_start);
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2 != 0)
	{
		print_status(philo, false, THINK);
		usleep(10000);
	}
	while (end_simulation(philo->table) == false)
		routine(philo);
	return (NULL);
}
