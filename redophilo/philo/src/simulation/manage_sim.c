/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 14:06:14 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_simulation(t_table *table)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&table->end_sim_lock);
	if (table->end_sim == true)
		end = true;
	pthread_mutex_unlock(&table->end_sim_lock);
	return (end);
}
