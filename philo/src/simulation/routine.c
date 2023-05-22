/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:58:53 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/22 23:47:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

static void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->fork[ph->id - 1]);
	print_status(ph, false, FORK);
	pthread_mutex_lock(&ph->table->fork[ph->id % ph->table->nbr_philo]);
	print_status(ph, false, FORK);
	print_status(ph, false, EAT);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = current_time();
	pthread_mutex_unlock(&ph->meal_lock);
	pthread_mutex_lock(&ph->times_lock);
	ph->times_ate++;
	pthread_mutex_unlock(&ph->times_lock);
	philo_wait(ph->table, EAT);
}

static void	routine(t_philo *ph)
{
	take_forks(ph);
	pthread_mutex_unlock(&ph->table->fork[ph->id - 1]);
	pthread_mutex_unlock(&ph->table->fork[ph->id % ph->table->nbr_philo]);
	print_status(ph, false, SLEEP);
	philo_wait(ph->table, SLEEP);
	print_status(ph, false, THINK);
}

static void	lonely_routine(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->fork[0]);
	print_status(ph, false, FORK);
	philo_wait(ph->table, DEAD);
	print_status(ph, true, DEAD);
	pthread_mutex_unlock(&ph->table->fork[0]);
	ph->table->end_sim = true;
}

/* Launches a routine:
* - before launching any routine, waits for all other threads to be created
	to start
* - if there is 1 philosopher, launches the routine for 1 philosopher
* - else launches the basic routine (eat, sleep and think)
*/
void	*launch_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->nbr_meals == 0 || philo->table->tm_starve == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = philo->table->tm_start;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_until_start(philo->table->tm_start);
	if (check_end(philo->table) == true)
		return (NULL);
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2 != 0)
	{
		print_status(philo, false, THINK);
		usleep(10000);
	}
	while (check_end(philo->table) == false)
		routine(philo);
	return (NULL);
}
