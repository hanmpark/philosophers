/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:23 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/03 13:51:29 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		return (error_exit(ERR_ARGS_NBR, EXIT_FAILURE));
	table = prepare_table(argc, argv);
	if (!table)
		return (error_exit(ERR_INIT_PHILO, EXIT_FAILURE));
	if (start_sim(table) == false)
		return (error_exit(ERR_INIT_DINING, EXIT_FAILURE));
	stop_sim(table);
	return (EXIT_SUCCESS);
}
