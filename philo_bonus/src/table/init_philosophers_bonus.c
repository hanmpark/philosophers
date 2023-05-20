/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/20 16:19:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"

bool	init_philosophers(t_table *table)
{
	unsigned int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
		return (init_error(ERR_PHILO, table, true));
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].times_ate = 0;
		table->philo[i].table = table;
		i++;
	}
	return (true);
}
