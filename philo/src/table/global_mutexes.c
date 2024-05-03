/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:31:49 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:38:00 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

/**
 * @brief Initializes the forks for the simulation.
 *
 * @param table A pointer to the t_table structure that contains
 * the simulation parameters.
 *
 * @return Returns true if the forks were successfully initialized.
 * Returns false if there was an error, such as a failed memory allocation
 * or a failed mutex initialization.
 */
static bool	init_forks(t_table *table)
{
	int	i;

	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t *));
	if (!table->fork)
		return (init_error(ERR_FORKS, table, false));
	i = -1;
	while (++i < table->nbr_philo)
	{
		table->fork[i] = malloc(sizeof(pthread_mutex_t));
		if (!table->fork[i] || pthread_mutex_init(table->fork[i], NULL))
			return (init_error(ERR_FORKS, table, false));
	}
	return (true);
}

/**
 * @brief Initializes the global mutexes for the simulation.
 *
 * @param table A pointer to the t_table structure that contains
 * the simulation parameters.
 *
 * @return Returns true if the global mutexes were successfully initialized.
 * Returns false if there was an error, such as a failed mutex initialization.
 */
bool	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->sim_lock, NULL))
		return (init_error(ERR_MUTEX, table, false));
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (init_error(ERR_MUTEX, table, false));
	if (!init_forks(table))
		return (false);
	return (true);
}
