/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:46:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/16 19:02:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"

/* Initializes processes:
* - each process represents a philosopher
* - if there is more than 1 philosopher, initializes the watcher's thread
*/
bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->tm_start = give_current_time() + (table->nbr_philo * 20);
	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
			init_error(ERR_PHILO, table, true);
		if (table->philo[i].pid == 0)
		{
			launch_routine(&table->philo[i]);
		}
		i++;
	}
}
