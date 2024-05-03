/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:59:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "errors_bonus.h"
#include "timer_bonus.h"
#include <signal.h>

/**
 * @brief Destroys the individual semaphores for each philosopher.
 *
 * Closes and unlinks the semaphore for each philosopher, and then frees the
 * memory allocated for the semaphore name.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
static void	destroy_individual_sem(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		sem_close(table->philo[i].meal_lock);
		sem_unlink(table->philo[i].nm_lock);
		free(table->philo[i].nm_lock);
	}
}

/**
 * @brief Destroys the global semaphores for the simulation.
 *
 * Calls the destroy_individual_sem function to destroy the individual
 * semaphores, and then closes and unlinks the global semaphores.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
static void	destroy_sem(t_table *table)
{
	destroy_individual_sem(table);
	sem_close(table->fork_lock);
	sem_close(table->print_lock);
	sem_close(table->sim_lock);
	sem_close(table->philo_full);
	sem_unlink("/fork_lock");
	sem_unlink("/print_lock");
	sem_unlink("/sim_lock");
	sem_unlink("/philo_full");
}

/**
 * @brief Kills all the philosophers in the simulation.
 *
 * Sends a SIGKILL signal to each philosopher.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 */
void	kill_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
		kill(table->philo[i].pid, SIGKILL);
}

/**
 * @brief Cleans up the simulation table.
 *
 * If the table is not NULL, destroys the semaphores if the semaphore parameter
 * is true, frees the memory allocated for the philosophers, and then frees the
 * memory allocated for the table.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 * @param semaphore A boolean indicating whether to destroy the semaphores.
 */
void	clean_table(t_table *table, bool semaphore)
{
	if (!table)
		return ;
	if (semaphore)
		destroy_sem(table);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}

/**
 * @brief Handles an initialization error.
 *
 * Cleans up the simulation table, and then writes the error message and the
 * help message to the standard error.
 *
 * @param msg The error message to write to the standard error.
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 * @param semaphore A boolean indicating whether to destroy the semaphores.
 *
 * @return Returns false.
 */
bool	init_error(char *msg, t_table *table, bool semaphore)
{
	if (table)
		clean_table(table, semaphore);
	while (*msg)
		write(2, &*msg++, sizeof(char));
	write(2, HELP, sizeof(HELP));
	return (false);
}
