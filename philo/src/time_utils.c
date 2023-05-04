/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:06 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/04 18:20:48 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_time(t_philo *philo, time_t wait)
{
	time_t	timemark;

	timemark = actual_time();
	while (actual_time() - timemark < wait)
	{
		if (sim_has_ended(philo) == true)
			break ;
		usleep(100);
	}
}
