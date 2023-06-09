/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:41:39 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 14:14:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"

time_t	give_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Waits for the given time in ms:
* - usleep() is not as precise as it should be
* - waits for wait_time in ms by using small intervals of usleep() call
*	for precision's sake
* - does not wait the end_sim flag is set to true during the loop
*/
void	*philo_wait(time_t wait_time)
{
	time_t	timestamp;

	timestamp = give_current_time();
	while (give_current_time() - timestamp < wait_time)
		usleep(100);
	return (NULL);
}
