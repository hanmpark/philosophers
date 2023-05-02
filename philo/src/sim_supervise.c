/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_supervise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:45:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/02 16:48:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_sim_bool(t_table *table, bool state)
{
	pthread_mutex_lock(&table->end_sim_lock);
	table->end_sim = state;
	pthread_mutex_unlock(&table->end_sim_lock);
}

static bool	is_dead(t_philo *philo)
{
	time_t	timestamp;

	timestamp = actual_time();
	if (timestamp - philo->last_eat >= philo->table->time_to_die)
	{
		set_sim_bool(philo->table, true);
		print_status(philo, DEAD);
		return (true);
	}
	return (false);
}

static bool	check_philo_health(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (is_dead(&table->philo[i]) == true)
			return 
		i++;
	}
}

void	*supervise_sim(t_table *table)
{
	if (table->dine_left == 0)
		return (NULL);
	set_sim_bool(table, false);
	wait_start_time(table->start_time);
	while (true)
	{
		if (check_philo_health(table) == true)
			set_sim_bool(table, true);
		
	}
}
