/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:20:16 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/06 19:11:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "print_status.h"

// A philosopher's routine in which he eats, sleeps and thinks
static void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->id - 1]);
	print_status(philo, false, FORK);
	pthread_mutex_lock(&philo->table->fork[philo->id % \
		philo->table->number_of_philo]);
	print_status(philo, false, FORK);
	print_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = actual_time();
	if (philo->table->number_of_meals > 0 && sim_has_ended(philo) == false)
		philo->times_eat++;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_time(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->fork[philo->id % \
		philo->table->number_of_philo]);
	print_status(philo, false, SLEEPING);
	wait_time(philo->table->time_to_sleep);
	print_status(philo, false, THINKING);
}

// A routine for a lone philosopher
void	*lonely_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->table->fork[0]);
	print_status(philo, false, FORK);
	wait_time(philo->table->time_to_die);
	print_status(philo, true, DEAD);
	pthread_mutex_unlock(&philo->table->fork[0]);
	return (NULL);
}

/* Launches an adapted routine or not depending on:
* - the number of philosophers
* - the philosophers' id
* - the set rules
*/
void	*launch_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->number_of_meals == 0 || philo->table->time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->id % 2 != 0)
	{
		print_status(philo, false, THINKING);
		wait_time(10);
	}
	while (sim_has_ended(philo) == false)
		philo_routine(philo);
	return (NULL);
}
