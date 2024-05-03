/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:44:28 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

/**
 * @brief Gets the current time in milliseconds.
 *
 * @return Returns the current time in milliseconds.
 */
time_t	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Waits until the specified time.
 *
 * @param time The time to wait until, in milliseconds.
 */
void	wait_until_start(time_t time)
{
	while (current_time() < time)
		usleep(100);
}

/**
 * @brief Waits for the given time in milliseconds.
 *
 * Waits for `wait_time` in milliseconds by using small intervals of `usleep()`
 * call for precision's sake. Does not wait if the `end_sim` flag is set to true
 * during the loop.
 *
 * @param table A pointer to the t_table structure that contains the simulation
 * parameters.
 * @param status The status of the philosopher (EAT, SLEEP, or DEAD).
 *
 * @return Returns NULL when the wait is over or if the `end_sim` flag is set to
 * true.
 */
void	*philo_wait(t_table *table, t_status status)
{
	time_t	timestamp;
	time_t	wait_time;

	timestamp = current_time();
	wait_time = 0;
	if (status == EAT)
		wait_time = table->tm_eat;
	else if (status == SLEEP)
		wait_time = table->tm_sleep;
	else if (status == DEAD)
		wait_time = table->tm_starve;
	while (current_time() - timestamp < wait_time)
	{
		if (check_sim_state(table) == true)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
