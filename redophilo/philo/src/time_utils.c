/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 14:22:39 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	give_actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_until_start(time_t start)
{
	while (give_actual_time() < start)
		usleep(100);
}

void	*philo_wait(t_table *table, t_status status)
{
	time_t	timestamp;
	time_t	wait_time;

	timestamp = give_actual_time();
	wait_time = 0;
	if (status == EAT)
		wait_time = table->tm_eat;
	else if (status == SLEEP)
		wait_time = table->tm_sleep;
	while (give_actual_time() - timestamp < wait_time)
	{
		if (end_simulation(table) == true)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}