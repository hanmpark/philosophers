/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:17:19 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/23 11:43:55 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static void	set_rules(t_table *table, int argc, char **argv)
{
	table->nbr_philo = philo_atoi(argv[1]);
	table->tm_starve = philo_atoi(argv[2]);
	table->tm_eat = philo_atoi(argv[3]);
	table->tm_sleep = philo_atoi(argv[4]);
	table->nbr_meals = -1;
	if (argc == 6)
		table->nbr_meals = philo_atoi(argv[5]);
	table->end_sim = false;
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	if (check_arguments(argc, argv) == false)
		return (NULL);
	table = NULL;
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	set_rules(table, argc, argv);
	if (init_global_sem(table) == false || init_philosophers(table) == false)
		return (NULL);
	return (table);
}
