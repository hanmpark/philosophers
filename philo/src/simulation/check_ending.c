/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:22:27 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 14:59:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

void	set_sim_state(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_lock);
	table->end_sim = state;
	pthread_mutex_unlock(&table->sim_lock);
}

bool	check_sim_state(t_table *table)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&table->sim_lock);
	if (table->end_sim)
		end = true;
	pthread_mutex_unlock(&table->sim_lock);
	return (end);
}
