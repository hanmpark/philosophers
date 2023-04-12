/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:33:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/12 17:25:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.c"

static void	philo_eat(t_table *table)
{
	int	left_fork;
	int	right_fork;

	left_fork = table->philo->id;
	right_fork = (table->philo->id + 1) % table->nbr_philo;
	pthread_mutex_lock(&table->fork[left_fork]);
	printf("%lli %d has taken a fork\n", actual_time(), table->philo->id);
	pthread_mutex_lock(&table->fork[right_fork]);
	printf("%lli %d has taken a fork\n", actual_time(), table->philo->id);
	printf("%lli %d is eating\n", actual_time(), table->philo->id);
	wait_time(table->tm_to_eat);
	pthread_mutex_unlock(&table->fork[left_fork]);
	pthread_mutex_unlock(&table->fork[right_fork]);
}

static void	philo_sleep_think(t_table *table)
{
	printf("%lli %d is sleeping\n", actual_time(), table->philo->id);
	wait_time(table->tm_to_sleep);
	printf("%lli %d is thinking\n", actual_time(), table->philo->id);
	wait_time(table->tm_to_die);
}

void	*philosopher_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	table->philo->last_eat = actual_time();
	while (!table->end)
	{
		philo_eat(table);
		philo_sleep_think(table);
	}
}