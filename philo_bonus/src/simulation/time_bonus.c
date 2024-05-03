/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:41:39 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:02:23 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

/**
 * @brief Gives the current time in milliseconds.
 *
 * Gets the current time using the gettimeofday function, and then converts it
 * to milliseconds.
 *
 * @return Returns the current time in milliseconds.
 */
time_t	give_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Waits for the given time in milliseconds.
 *
 * Waits for the given time in milliseconds by using small intervals of usleep
 * calls for precision's sake. Does not wait if the end_sim flag is set to true
 * during the loop.
 *
 * @param wait_time The time to wait in milliseconds.
 *
 * @return Returns NULL.
 */
void	*philo_wait(time_t wait_time)
{
	time_t	timestamp;

	timestamp = give_current_time();
	while (give_current_time() - timestamp < wait_time)
		usleep(100);
	return (NULL);
}
