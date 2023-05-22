/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:00:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/22 14:46:51 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"

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
