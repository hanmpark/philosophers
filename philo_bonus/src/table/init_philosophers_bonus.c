/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:00:06 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/12 15:12:35 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static sem_t	sem_name_philo(const char *name, int philo_id)
{
	
}

bool	init_philosophers(t_table *table)
{
	unsigned int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
		return (false);
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].times_sem = sem_name_philo();
		if (table->philo[i].times_sem == SEM_FAILED)
			return (false);
		table->philo[i].id = i + 1;
		table->philo[i].times_ate = 0;
		i++;
	}
}
