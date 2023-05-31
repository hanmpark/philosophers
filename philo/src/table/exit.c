/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 14:04:39 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "errors.h"
#include "timer.h"

static void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i].meal_lock);
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->sim_lock);
	pthread_mutex_destroy(&table->print_lock);
}

void	clean_table(t_table *table, bool mutex)
{
	if (!table)
		return ;
	if (mutex)
		destroy_mutexes(table);
	if (table->fork != NULL)
		free(table->fork);
	if (table->philo != NULL)
		free(table->philo);
	free(table);
}

bool	init_error(char *msg, t_table *table, bool mutex)
{
	if (table)
		clean_table(table, mutex);
	while (*msg)
		write(2, &*msg++, sizeof(char));
	write(2, HELP, sizeof(HELP));
	return (false);
}
