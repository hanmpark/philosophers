/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:31:49 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/22 23:09:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

static bool	init_forks(t_table *table)
{
	unsigned int	i;

	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (init_error(ERR_FORKS, table, false));
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (init_error(ERR_FORKS, table, false));
		i++;
	}
	return (true);
}

bool	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
		return (init_error(ERR_MUTEX, table, false));
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (init_error(ERR_MUTEX, table, false));
	if (init_forks(table) == false)
		return (false);
	return (true);
}
