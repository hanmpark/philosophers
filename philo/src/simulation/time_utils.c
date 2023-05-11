/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 15:22:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"

time_t	give_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_until_start(time_t start)
{
	while (give_current_time() < start)
		usleep(100);
}

/* Waits for the given time in ms:
* - usleep() is not as precise as it should be
* - waits for wait_time in ms by using small intervals of usleep() call
*	for precision's sake
* - does not wait the end_sim flag is set to true during the loop
*/
void	*philo_wait(t_table *table, t_status status)
{
	time_t	timestamp;
	time_t	wait_time;

	timestamp = give_current_time();
	wait_time = 0;
	if (status == EAT)
		wait_time = table->tm_eat;
	else if (status == SLEEP)
		wait_time = table->tm_sleep;
	else if (status == DEAD)
		wait_time = table->tm_starve;
	while (give_current_time() - timestamp < wait_time)
	{
		if (end_simulation(table) == true)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}