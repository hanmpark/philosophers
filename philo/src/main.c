/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:33:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

/**
 * @brief Main function of the program.
 * It initializes the simulation, starts it, and then ends it.
 *
 * @param argc The number of arguments.
 * @param argv An array of strings representing the arguments.
 *
 * @return Returns 0 if the simulation ran successfully.
 */
int	main(int argc, char **argv)
{
	t_table	*table;

	memset(&table, 0, sizeof(t_table));
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (!start_simulation(table))
		return (2);
	end_simulation(table);
	return (0);
}
