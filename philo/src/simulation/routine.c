/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:58:53 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 17:03:21 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

static void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->fork[ph->id - 1]);
	print_status(ph, false, FORK);
	pthread_mutex_lock(&ph->table->fork[ph->id % ph->table->nbr_philo]);
	print_status(ph, false, FORK);
	print_status(ph, false, EAT);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = current_time();
	ph->times_ate++;
	pthread_mutex_unlock(&ph->meal_lock);
	philo_wait(ph->table, EAT);
	pthread_mutex_unlock(&ph->table->fork[ph->id - 1]);
	pthread_mutex_unlock(&ph->table->fork[ph->id % ph->table->nbr_philo]);
}

static void	routine(t_philo *ph)
{
	eat(ph);
	print_status(ph, false, SLEEP);
	philo_wait(ph->table, SLEEP);
	print_status(ph, false, THINK);
}

static void	lonely_routine(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->fork[0]);
	print_status(ph, false, FORK);
	philo_wait(ph->table, DEAD);
	pthread_mutex_unlock(&ph->table->fork[0]);
}

/* Launches a routine:
* - if there is 1 philosopher, launches the routine for 1 philosopher
* - else launches the basic routine (eat, sleep and think)
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
