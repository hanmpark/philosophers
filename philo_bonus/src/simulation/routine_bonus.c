/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 13:03:11 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	print_status(philo, false, EAT);
	sem_wait(philo->meal_lock);
	philo->last_meal = give_current_time();
	if (++philo->count_meal == philo->table->nbr_meals)
		sem_post(philo->table->ate_enough);
	sem_post(philo->meal_lock);
	philo_wait(philo->table, philo->table->tm_eat);
	sem_post(philo->table->fork_lock);
	sem_post(philo->table->fork_lock);
}

static void	routine(t_philo *philo)
{
	eat(philo);
	print_status(philo, false, SLEEP);
	philo_wait(philo->table, philo->table->tm_sleep);
	print_status(philo, false, THINK);
}

static void	lonely_routine(t_philo *philo)
{
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	philo_wait(philo->table, philo->table->tm_starve);
	print_status(philo, true, DEAD);
	sem_post(philo->table->sim_lock);
}

/* Launches a routine:
* - if there is 1 philosopher, launches lonely_routine()
* - else launches the basic routine (eat, sleep and think)
*/
void	*launch_routine(t_philo *philo)
{
	if (!philo->table->nbr_meals)
		exit(EXIT_SUCCESS);
	else if (!philo->table->tm_starve)
	{
		print_status(philo, true, DEAD);
		sem_post(philo->table->sim_lock);
		exit(EXIT_SUCCESS);
	}
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2)
	{
		print_status(philo, false, THINK);
		philo_wait(philo->table, 10);
	}
	while ("Philosophers are annoying")
		routine(philo);
	return (NULL);
}
