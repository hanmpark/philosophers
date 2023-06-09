/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/25 19:31:58 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"
#include <signal.h>

static bool	init_individual_sem(t_philo *ph, unsigned int number)
{
	ph->nm_lock = individual_sem_name("/meal_lock", number);
	if (!ph->nm_lock)
		return (init_error(ERR_SEM, ph->table, false));
	sem_unlink(ph->nm_lock);
	ph->meal_lock = sem_open(ph->nm_lock, O_CREAT | O_EXCL, 0664, 1);
	if (ph->meal_lock == SEM_FAILED)
		return (init_error(ERR_SEM, ph->table, false));
	return (true);
}

bool	init_philosophers(t_table *table)
{
	unsigned int	i;

	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
		return (init_error(ERR_PHILO, table, false));
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].count_meal = 0;
		table->philo[i].table = table;
		if (init_individual_sem(&table->philo[i], i + 1) == false)
			return (false);
		i++;
	}
	return (true);
}
