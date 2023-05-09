/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 15:41:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = give_actual_time() + (table->nbr_philo * 20);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &launch_routine, \
			&table->philo[i]) != 0)
			return (false);
		i++;
	}
	if (table->nbr_philo > 1)
	{
		if (pthread_create(&table->watcher, NULL, &watcher, table) != 0)
			return (false);
	}
	return (true);
}

static void	destroy_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i].philo_lock);
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

bool	stop_simulation(t_table *table)
{
	unsigned int	i;
	bool			clear_end;

	i = 0;
	clear_end = true;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			clear_end = false;
		i++;
	}
	if (table->nbr_philo > 1)
	{
		if (pthread_join(table->watcher, NULL) != 0)
			clear_end = false;
	}
	clean_table(table);
	return (clear_end);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (start_simulation(table) == false)
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}