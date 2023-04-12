/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:14:56 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/12 11:47:37 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initialize the mutexes (forks)
static void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
}

// Initialize the threads (philsophers) and start the routines
static void	init_philo(t_table *table)
{
	int	i;
	int	*id;

	i = 0;
	table->end = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].state = ALIVE;
		pthread_create(&table->philo[i].thread, NULL, &philosopher_routine, table);
		i++;
	}
}

// Initialize the mutexes (forks) and philosophers (threads)
void	init_dining(t_table *table)
{
	if (table->nbr_philo < 1)
		ft_error(ERR_PHILO);
	table->fork = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->fork)
		ft_error(ERR_MALLOC);
	table->philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!table->philo)
	{
		free(table->fork);
		ft_error(ERR_MALLOC);
	}
	init_forks(table);
	init_philo(table);
}

static int	init_config(t_table *table, int argc, char **argv)
{
	table->nbr_philo = set_int(argv[1]);
	table->tm_death = set_int(argv[2]);
	table->tm_dine = set_int(argv[3]);
	table->tm_sleep = set_int(argv[4]);
	if (argc == 6)
		table->nbr_eat = set_int(argv[5]);
	else
		table->nbr_eat = -1;
	if (table->nbr_philo < 0 || table->tm_death < 0 || table->tm_dine < 0 || \
		table->tm_sleep < 0 || (argc == 6 && table->nbr_eat < 0))
		return (-1);
	return (0);
}

static void	set_table(t_table *table)
{
	if (table->nbr_philo < 1)
		
}

int	init_philo(t_table *table, int argc, char **argv)
{
	if (init_config(table, argc, argv) == -1)
		return (-1);
	set_table(table);
}