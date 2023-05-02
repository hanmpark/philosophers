/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:51:20 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/02 13:47:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Philosophers should eat sleep and think
bool	start_sim(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = actual_time() + (table->number_of_philo * 20);
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_routine, \
			&table->philo[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &supervise_sim, &table) != 0)
		return (false);
	return (true);
}
