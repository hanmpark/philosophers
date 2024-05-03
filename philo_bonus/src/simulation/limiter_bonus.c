/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:05:20 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:06:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/**
 * @brief Limiter's thread function.
 *
 * If the number of meals is set to 0, it stops the simulation. If the number
 * of meals is greater than 0, it waits for all the philosophers to eat at
 * least that number of meals before stopping the simulation.
 *
 * @param arg A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns NULL.
 */
void	*limiter(void *arg)
{
	t_table	*table;
	int		fulfilled_meals;

	table = (t_table *)arg;
	if (!table->nbr_meals)
	{
		sem_post(table->sim_lock);
		return (NULL);
	}
	if (!table->tm_starve)
		return (NULL);
	fulfilled_meals = 0;
	while (fulfilled_meals < table->nbr_philo && !table->end_sim)
	{
		sem_wait(table->philo_full);
		fulfilled_meals++;
	}
	sem_post(table->sim_lock);
	return (NULL);
}
