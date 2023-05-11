/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:33:38 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 15:38:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"

bool	init_philosophers(t_table *table)
{
	unsigned int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
		table_error(ERR_PHILO, table, 0, table->nbr_philo);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->philo[i].philo_lock, NULL) != 0)
			return (table_error(ERR_PHILO, table, i, table->nbr_philo));
		table->philo[i].id = i + 1;
		table->philo[i].times_ate = 0;
		table->philo[i].table = table;
		i++;
	}
	return (true);
}
