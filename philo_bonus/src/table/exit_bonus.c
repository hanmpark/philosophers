/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/21 17:15:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "errors_bonus.h"
#include "timer_bonus.h"
#include <signal.h>

static void	putstr_error(char *msg)
{
	while (*msg)
		write(2, &*msg++, sizeof(char));
}

static void	destroy_semaphores(t_table *table)
{
	sem_close(table->fork_sem);
	sem_close(table->print_sem);
	sem_close(table->sim_sem);
	sem_close(table->ate_enough);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/sim_sem");
	sem_unlink("/ate_enough");
}

void	kill_philosophers(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		kill(table->philo[i].pid, SIGKILL);
		i++;
	}
}

void	clean_table(t_table *table, bool semaphore)
{
	if (!table)
		return ;
	if (semaphore)
		destroy_semaphores(table);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}

bool	init_error(char *msg, t_table *table, bool semaphore)
{
	if (table)
		clean_table(table, semaphore);
	putstr_error(msg);
	return (false);
}
