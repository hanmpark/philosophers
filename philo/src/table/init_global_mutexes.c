/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_mutexes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:31:49 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 15:55:16 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

static bool	init_forks(t_table *table)
{
	unsigned int	i;

	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (msg_error(ERR_FORKS, NULL, 0, 0));
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (bool_error(ERR_FORKS, table, NULL));
		i++;
	}
	return (true);
}

bool	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->end_sim_lock, NULL) != 0)
		return (bool_error(ERR_MUTEX, NULL, ));
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (bool_error(ERR_MUTEX, table->fork, NULL));
	if (init_forks(table) == false)
		return (false);
	return (true);
}
