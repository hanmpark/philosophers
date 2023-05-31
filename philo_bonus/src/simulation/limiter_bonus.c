/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:05:20 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 13:02:17 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/* Limiter's thread:
* - if the nbr_meals is set to 0 stop the simulation
* - if the nbr_meals > 0, waits for all the philosophers to eat
*	at least nbr_meals time before stopping the simulation
*/
void	*limiter(void *arg)
{
	unsigned int	fulfilled_meals;
	t_table			*table;

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
		sem_wait(table->ate_enough);
		fulfilled_meals++;
	}
	sem_post(table->sim_lock);
	return (NULL);
}
