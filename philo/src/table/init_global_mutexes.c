/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_mutexes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:31:49 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 15:15:06 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

static bool	init_forks(t_table *table)
{
	unsigned int	i;

	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
	{
		pthread_mutex_destroy(&table->sim_lock);
		pthread_mutex_destroy(&table->print_lock);
		return (table_error(ERR_FORKS, table, 0, 0));
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (table_error(ERR_FORKS, table, 0, i));
		i++;
	}
	return (true);
}

bool	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
		return (table_error(ERR_MUTEX, table, 0, 0));
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->sim_lock);
		return (table_error(ERR_MUTEX, table, 0, 0));
	}
	if (init_forks(table) == false)
		return (false);
	return (true);
}
