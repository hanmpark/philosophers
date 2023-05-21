/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/21 18:00:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->fork_sem);
	print_status(philo, FORK);
	sem_wait(philo->table->fork_sem);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->last_meal = give_current_time();
	philo->times_ate++;
	if (philo->table->nbr_meals > 0 && \
		philo->times_ate >= philo->table->nbr_meals)
		sem_post(philo->table->sim_sem);
	philo_wait(philo->table, EAT);
}

static void	routine(t_philo *philo)
{
	take_forks(philo);
	sem_post(philo->table->fork_sem);
	sem_post(philo->table->fork_sem);
	print_status(philo, SLEEP);
	philo_wait(philo->table, SLEEP);
	print_status(philo, THINK);
}

static void	lonely_routine(t_philo *philo)
{
	sem_wait(philo->table->fork_sem);
	print_status(philo, FORK);
	philo_wait(philo->table, DEAD);
	print_status(philo, DEAD);
	sem_post(philo->table->sim_sem);
}

/* Launches a routine:
* - before launching any routine, waits for all other processes to be created
	to start
* - if there is 1 philosopher, launches the routine for 1 philosopher
* - else launches the basic routine (eat, sleep and think)
*/
void	*launch_routine(t_philo *philo)
{
	if (philo->table->nbr_meals == 0 || philo->table->tm_starve == 0)
		return (NULL);
	philo->last_meal = philo->table->tm_start;
	if (philo->table->nbr_philo > 1)
		if (pthread_create(&philo->hunger_watcher, NULL, \
			&hunger_watcher, philo))
			return (NULL);
	wait_until_start(philo->table->tm_start);
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2 != 0)
	{
		print_status(philo, THINK);
		usleep(10000);
	}
	while ("Philosophers are annoying")
		routine(philo);
	return (NULL);
}
