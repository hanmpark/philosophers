/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:05:37 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/**
 * @brief Simulates a philosopher eating.
 *
 * The philosopher waits for access to forks, eats, and then releases the forks.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 */
static void	eat(t_philo *philo)
{
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	print_status(philo, false, EAT);
	sem_wait(philo->meal_lock);
	philo->last_meal = give_current_time();
	if (philo->table->nbr_meals != -1 && \
		++philo->count_meal == philo->table->nbr_meals)
		sem_post(philo->table->philo_full);
	sem_post(philo->meal_lock);
	philo_wait(philo->table->tm_eat);
	sem_post(philo->table->fork_lock);
	sem_post(philo->table->fork_lock);
}

/**
 * @brief Simulates a philosopher's routine.
 *
 * The philosopher eats, sleeps, and then thinks.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 */
static void	routine(t_philo *philo)
{
	eat(philo);
	print_status(philo, false, SLEEP);
	philo_wait(philo->table->tm_sleep);
	print_status(philo, false, THINK);
}

/**
 * @brief Simulates a lonely philosopher's routine.
 *
 * The lonely philosopher waits for a fork, then starves.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 */
static void	lonely_routine(t_philo *philo)
{
	sem_wait(philo->table->fork_lock);
	print_status(philo, false, FORK);
	philo_wait(philo->table->tm_starve);
	print_status(philo, true, DEAD);
	sem_post(philo->table->sim_lock);
}

/**
 * @brief Launches a philosopher's routine.
 *
 * Depending on the conditions, it launches a lonely routine or a regular routine.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 *
 * @return Returns NULL.
 */
void	*launch_routine(t_philo *philo)
{
	if (!philo->table->nbr_meals)
		exit(0);
	else if (!philo->table->tm_starve)
	{
		print_status(philo, true, DEAD);
		sem_post(philo->table->sim_lock);
		exit(0);
	}
	if (philo->table->nbr_philo == 1)
		lonely_routine(philo);
	else if (philo->id % 2)
	{
		print_status(philo, false, THINK);
		philo_wait(10);
	}
	while ("Philosophers are annoying")
		routine(philo);
	return (NULL);
}
