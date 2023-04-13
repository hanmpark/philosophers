/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:23 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/13 15:27:12 by hanmpark         ###   ########.fr       */
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
	return (0);
}
