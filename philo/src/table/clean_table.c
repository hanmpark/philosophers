/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:00:29 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 15:54:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static void	destroy_mutexes(t_table *table, int nbr_lock, int nbr_fork)
{
	int	i;

	i = -1;
	while (++i < nbr_lock)
		pthread_mutex_destroy(&table->philo[i].philo_lock);
	i = -1;
	while (++i < nbr_fork)
		pthread_mutex_destroy(&table->fork[i]);
	pthread_mutex_destroy(&table->end_sim_lock);
	pthread_mutex_destroy(&table->print);
}

void	clean_table(t_table *table, int nbr_lock, int nbr_fork)
{
	if (!table)
		return ;
	destroy_mutexes(table, nbr_lock, nbr_fork);
	if (table->fork != NULL)
		free(table->fork);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}
