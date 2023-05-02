/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:06 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/02 12:53:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_start_time(time_t start_time)
{
	while (actual_time() < start_time)
		usleep(10);
}

time_t	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_time(time_t wait)
{
	time_t	timemark;

	timemark = actual_time();
	while (actual_time() - timemark < wait)
		usleep(100);
}
