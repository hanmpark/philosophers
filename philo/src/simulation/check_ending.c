/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:22:27 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:51:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

/**
 * @brief Sets the simulation state.
 *
 * Locks the simulation mutex, sets the `end_sim` flag to the given state, and
 * then unlocks the simulation mutex.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 * @param state The state to set the `end_sim` flag to.
 */
void	set_sim_state(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_lock);
	table->end_sim = state;
	pthread_mutex_unlock(&table->sim_lock);
}

/**
 * @brief Checks the simulation state.
 *
 * Locks the simulation mutex, checks the `end_sim` flag, and if it's true, sets
 * the `end` variable to true. Then unlocks the simulation mutex and returns the
 * value of the `end` variable.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 *
 * @return Returns true if the `end_sim` flag is set to true, and false 
 * otherwise.
 */
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
