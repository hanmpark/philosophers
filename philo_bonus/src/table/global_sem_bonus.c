/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_sem_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:20:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/25 12:49:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include <signal.h>

bool	init_global_sem(t_table *table)
{
	sem_unlink("/fork_lock");
	sem_unlink("/print_lock");
	sem_unlink("/sim_lock");
	sem_unlink("/ate_enough");
	table->fork_lock = sem_open("/fork_lock", O_CREAT, S_IRUSR | S_IWUSR, \
		table->nbr_philo);
	if (table->fork_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->print_lock = sem_open("/print_lock", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->print_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->sim_lock = sem_open("/sim_lock", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (table->sim_lock == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	table->ate_enough = sem_open("/ate_enough", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (table->ate_enough == SEM_FAILED)
		return (init_error(ERR_SEM, table, false));
	return (true);
}
