/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 15:40:06 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "errors.h"
#include "timer.h"

static void	putstr_error(char *msg)
{
	while (*msg)
		write(2, &*msg++, sizeof(char));
}

bool	table_error(char *msg, t_table *table, int nbr_lock, int nbr_fork)
{
	clean_table(table, nbr_lock, nbr_fork);
	putstr_error(msg);
	return (false);
}

bool	thread_error(char *msg, t_table *table, int nbr_thread)
{
	int	i;

	set_sim_bool(table, true);
	wait_until_start(table->tm_start);
	i = -1;
	while (++i < nbr_thread)
		pthread_join(table->philo[i].thread, NULL);
	clean_table(table, table->nbr_philo, table->nbr_philo);
	putstr_error(msg);
	return (false);
}
