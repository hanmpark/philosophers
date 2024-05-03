/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:17:19 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:54:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

/**
 * @brief Sets the rules for the simulation.
 *
 * Sets the number of philosophers, the time before a philosopher starves, the
 * time it takes for a philosopher to eat, and the time a philosopher sleeps.
 * If a sixth argument is provided, sets the number of meals each philosopher
 * must eat. Otherwise, sets the number of meals to -1. Sets the `end_sim` flag
 * to false.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed to the
 * program.
 */
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

/**
 * @brief Initializes the simulation table.
 *
 * Checks the arguments passed to the program. If they are valid, allocates
 * memory for the simulation table, sets the rules for the simulation, and
 * initializes the global semaphore and the philosophers. If there is an error
 * during any of these steps, returns NULL.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of strings representing the arguments passed to the
 * program.
 *
 * @return Returns a pointer to the initialized t_table structure if the
 * initialization was successful, and NULL otherwise.
 */
t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	if (!check_arguments(argc, argv))
		return (NULL);
	table = NULL;
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	set_rules(table, argc, argv);
	if (!init_global_sem(table) || !init_philosophers(table))
		return (NULL);
	return (table);
}
