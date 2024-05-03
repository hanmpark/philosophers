/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:33:38 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:36:35 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

/**
 * @brief Initializes the philosophers for the simulation.
 *
 * @param table A pointer to the t_table structure that contains
 * the simulation parameters.
 *
 * @return Returns true if the philosophers were successfully initialized.
 * Returns false if there was an error, such as a failed memory allocation
 * or a failed mutex initialization.
 */
bool	init_philosophers(t_table *table)
{
	int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo *));
	if (!table->philo)
		init_error(ERR_PHILO, table, false);
	i = -1;
	while (++i < table->nbr_philo)
	{
		table->philo[i] = malloc(sizeof(t_philo));
		if (!table->philo[i])
			return (init_error(ERR_PHILO, table, false));
		if (!table->philo[i] || \
			pthread_mutex_init(&table->philo[i]->meal_lock, NULL))
			return (init_error(ERR_PHILO, table, false));
		table->philo[i]->id = i + 1;
		table->philo[i]->times_ate = 0;
		table->philo[i]->table = table;
	}
	return (true);
}
