/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:58:53 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/19 09:34:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->id - 1]);
	print_status(philo, false, FORK);
	pthread_mutex_lock(&philo->table->fork[philo->id % philo->table->nbr_philo]);
	print_status(philo, false, FORK);
	print_status(philo, false, EAT);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = give_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->times_lock);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->times_lock);
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
	philo_wait(philo->table, DEAD);
	print_status(philo, true, DEAD);
	pthread_mutex_unlock(&philo->table->fork[0]);
	philo->table->end_sim = true;
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
	if (end_simulation(philo->table) == true)
		return (NULL);
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
