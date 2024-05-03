/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:00:52 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:53:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

/**
 * @brief The main function of the program.
 *
 * Initializes the simulation table, starts the simulation, and then ends the
 * simulation. If there is an error during the initialization or the start of
 * the simulation, returns 1 or 2 respectively. Otherwise, returns 0.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed to the
 * program.
 *
 * @return Returns 0 if the simulation ran successfully, 1 if there was an error
 * during the initialization, and 2 if there was an error during the start of
 * the simulation.
 */
int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (!start_simulation(table))
		return (2);
	end_simulation(table);
	return (0);
}
