/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:12:54 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:42:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "table_tools.h"

// Install philosophers to the table and initialize their variables
static t_philo	*install_philos(t_table *table)
{
	t_philo			*philo;
	unsigned int	i;

	philo = malloc(table->number_of_philo * sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
		{
			free(philo);
			return (NULL);
		}
		philo[i].id = i + 1;
		philo[i].times_eat = 0;
		philo[i].table = table;
		i++;
	}
	return (philo);
}

// Initialize forks (mutexes)
static bool	init_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->fork = malloc(table->number_of_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (false);
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
		{
			free(table->fork);
			return (false);
		}
		i++;
	}
	return (true);
}

// Initialize mutexes needed to make the simulation work
static bool	init_global_mutexes(t_table *table)
{
	if (init_forks(table) == false)
		return (false);
	if (pthread_mutex_init(&table->end_sim_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (false);
	return (true);
}

// Initialize the rules that each philosopher has to respect
static void	set_rules(t_table *table, int argc, char **argv)
{
	table->number_of_philo = philo_atoi(argv[1]);
	table->time_to_die = philo_atoi(argv[2]);
	table->time_to_eat = philo_atoi(argv[3]);
	table->time_to_sleep = philo_atoi(argv[4]);
	table->number_of_meals = -1;
	if (argc == 6)
		table->number_of_meals = philo_atoi(argv[5]);
	table->end_sim = false;
}

// Parse and set every data to launch the simulation
t_table	*prepare_table(int argc, char **argv)
{
	t_table	*table;

	if (valid_input(argc, argv) == false)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	set_rules(table, argc, argv);
	table->philo = install_philos(table);
	if (!table->philo)
	{
		free(table);
		return (NULL);
	}
	if (init_global_mutexes(table) == false)
	{
		free(table->philo);
		free(table);
		return (NULL);
	}
	return (table);
}
