/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:05:20 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

// If all the philosophers have eaten at least nbr_meals time, stop the sim
void	*limiter(void *arg)
{
	unsigned int	fulfilled_meals;
	t_table			*table;

	table = (t_table *)arg;
	if (table->nbr_philo < 2 || table->nbr_meals <= 0 || table->tm_starve == 0)
		return (NULL);
	wait_until_start(table->tm_start);
	fulfilled_meals = 0;
	while (fulfilled_meals < table->nbr_philo && table->end_sim == false)
	{
		sem_wait(table->ate_enough);
		fulfilled_meals++;
	}
	sem_post(table->sim_lock);
	return (NULL);
}
