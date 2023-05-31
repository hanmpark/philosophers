/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 14:09:10 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "errors_bonus.h"
#include "timer_bonus.h"
#include <signal.h>

static void	destroy_individual_sem(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		sem_close(table->philo[i].meal_lock);
		sem_unlink(table->philo[i].nm_lock);
		free(table->philo[i].nm_lock);
		i++;
	}
}

static void	destroy_sem(t_table *table)
{
	destroy_individual_sem(table);
	sem_close(table->fork_lock);
	sem_close(table->print_lock);
	sem_close(table->sim_lock);
	sem_close(table->ate_enough);
	sem_unlink("/fork_lock");
	sem_unlink("/print_lock");
	sem_unlink("/sim_lock");
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
		destroy_sem(table);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}

bool	init_error(char *msg, t_table *table, bool semaphore)
{
	if (table)
		clean_table(table, semaphore);
	while (*msg)
		write(2, &*msg++, sizeof(char));
	write(2, HELP, sizeof(HELP));
	return (false);
}
