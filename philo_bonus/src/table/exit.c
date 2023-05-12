/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/12 14:18:46 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "errors_bonus.h"
#include "timer_bonus.h"

static void	putstr_error(char *msg)
{
	while (*msg)
		write(2, &*msg++, sizeof(char));
}

static void	destroy_semaphores(t_table *table)
{
	unsigned int	i;

	i = 0;
	sem_close(table->fork_sem);
	sem_close(table->print_sem);
	sem_unlink("/fork");
	sem_unlink("/print");
}

void	clean_table(t_table *table, bool semaphore)
{
	if (!table)
		return ;
	if (semaphore == true)
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
