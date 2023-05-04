/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:51:20 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/04 15:26:18 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Philosophers should eat sleep and think
bool	start_sim(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->start_time = actual_time();
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_routine, \
			&table->philo[i]) != 0)
			return (false);
		usleep(15);
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &sim_supervise, table) != 0)
		return (false);
	return (true);
}

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

static void	clean_table(t_table *table)
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

void	stop_sim(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	if (table->number_of_philo > 1)
		pthread_join(table->watcher, NULL);
	clean_table(table);
}
