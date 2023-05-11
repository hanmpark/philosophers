/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:10:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 14:28:16 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (start_simulation(table) == false)
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
