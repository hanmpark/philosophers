/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:04 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:55:55 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include <signal.h>

/**
 * @brief Initializes an individual semaphore for a philosopher.
 *
 * Creates a unique name for the semaphore, unlinks any existing semaphore with
 * the same name, and then creates a new semaphore with that name. If there is
 * an error during any of these steps, returns false.
 *
 * @param ph A pointer to the t_philo structure representing the philosopher.
 * @param number The number of the philosopher.
 *
 * @return Returns true if the semaphore was successfully initialized, and false
 * otherwise.
 */
static bool	init_individual_sem(t_philo *ph, unsigned int number)
{
	ph->nm_lock = individual_sem_name("/meal_lock", number);
	if (!ph->nm_lock)
		return (init_error(ERR_SEM, ph->table, false));
	sem_unlink(ph->nm_lock);
	ph->meal_lock = sem_open(ph->nm_lock, O_CREAT | O_EXCL, 0664, 1);
	if (ph->meal_lock == SEM_FAILED)
		return (init_error(ERR_SEM, ph->table, false));
	return (true);
}

/**
 * @brief Initializes the philosophers for the simulation.
 *
 * Allocates memory for the philosophers, sets their id and table, and
 * initializes their individual semaphore. If there is an error during any of
 * these steps, returns false.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if the philosophers were successfully initialized, and
 * false otherwise.
 */
bool	init_philosophers(t_table *table)
{
	int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
		return (init_error(ERR_PHILO, table, false));
	i = -1;
	while (++i < table->nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].count_meal = 0;
		table->philo[i].table = table;
		if (init_individual_sem(&table->philo[i], i + 1) == false)
			return (false);
	}
	return (true);
}
