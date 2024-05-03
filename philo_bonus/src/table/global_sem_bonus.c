/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_sem_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:20:04 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:58:05 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include <signal.h>

/**
 * @brief Initializes the global semaphores for the simulation.
 *
 * Unlinks any existing semaphores with the names "/fork_lock", "/print_lock",
 * "/sim_lock", and "/philo_full", and then creates new semaphores with these
 * names. If there is an error during the creation of any of these semaphores,
 * returns false.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if the semaphores were successfully initialized, and
 * false otherwise.
 */
bool	init_global_sem(t_table *table)
{
	sem_unlink("/fork_lock");
	sem_unlink("/print_lock");
	sem_unlink("/sim_lock");
	sem_unlink("/philo_full");
	table->fork_lock = sem_open("/fork_lock", O_CREAT | O_EXCL, 0664, \
		table->nbr_philo);
	if (table->fork_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->print_lock = sem_open("/print_lock", O_CREAT | O_EXCL, 0664, 1);
	if (table->print_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->sim_lock = sem_open("/sim_lock", O_CREAT | O_EXCL, 0664, 0);
	if (table->sim_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->philo_full = sem_open("/philo_full", O_CREAT | O_EXCL, 0664, 0);
	if (table->philo_full == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	return (true);
}
