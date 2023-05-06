/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:36:37 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/06 16:59:31 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

// Checks if the simulation has ended or not
bool	sim_has_ended(t_philo *philo)
{
	bool	has_ended;

	has_ended = false;
	pthread_mutex_lock(&philo->table->end_sim_lock);
	if (philo->table->end_sim == true)
		has_ended = true;
	pthread_mutex_unlock(&philo->table->end_sim_lock);
	return (has_ended);
}

static void	destroy_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_destroy(&table->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->end_sim_lock);
	pthread_mutex_destroy(&table->print);
}

// Destroy mutexes and free the allocations
void	clean_table(t_table *table)
{
	if (!table)
		return ;
	destroy_mutex(table);
	if (table->fork != NULL)
		free(table->fork);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}
