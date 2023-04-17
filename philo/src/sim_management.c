/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:52:07 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/16 16:02:23 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_dining(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = actual_time() + (table->number_of_philo * 20);
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]) != 0)
			return (0);
		i++;
	}
}
