/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_mutexes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:31:49 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 14:15:06 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_forks(t_table *table)
{
	unsigned int	i;

	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (bool_error(ERR_FORKS, NULL, NULL));	
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (bool_error(ERR_FORKS, table->fork, NULL));
		i++;
	}
	return (true);
}

bool	init_global_mutexes(t_table *table)
{
	if (init_forks(table) == false)
		return (false);
	if (pthread_mutex_init(&table->end_sim_lock, NULL) != 0)
		return (bool_error(ERR_MUTEX, table->fork, NULL));
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (bool_error(ERR_MUTEX, table->fork, NULL));
	return (true);
}
