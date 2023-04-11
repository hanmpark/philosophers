/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:14:56 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/11 15:41:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initialize the mutexes (forks)
static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

// Initialize the threads (philsophers) and start the routines
static void	init_philosophers(t_data *data)
{
	int	i;
	int	*id;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->id = malloc(sizeof(int));
		*data->id = i;
		pthread_create(&data->philosopher[i], NULL, &philosopher_routine, data);
		i++;
	}
}

// Initialize the mutexes (forks) and philosophers (threads)
void	init_dining(t_data *data)
{
	if (data->nbr_philo < 1)
		ft_error(ERR_PHILO);
	data->fork = malloc(data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->fork)
		ft_error(ERR_MALLOC);
	data->philosopher = malloc(data->nbr_philo * sizeof(pthread_t));
	if (!data->philosopher)
	{
		free(data->fork);
		ft_error(ERR_MALLOC);
	}
	init_forks(data);
	init_philosophers(data);
}