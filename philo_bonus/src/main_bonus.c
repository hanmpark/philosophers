/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:00:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/06 17:13:46 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "errors_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		return (error_exit(ERR_ARGS_NBR));
	table = prepare_table(argc, argv);
	if (!table)
		return (error_exit(ERR_INIT_PHILO));
	if (start_sim(table) == false)
		return (error_exit(ERR_INIT_SIM));
	if (stop_sim(table) == false)
		return (error_exit(ERR_END_SIM));
	return (EXIT_SUCCESS);
}
