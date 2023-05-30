/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:01:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 15:12:34 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"
#include <stdio.h>

void	*print_status(t_philo *philo, bool last, t_status status)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (check_sim_state(philo->table) && !last)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (NULL);
	}
	timestamp = current_time() - philo->table->tm_start;
	if (status == DEAD)
		printf(MSG_DEAD, timestamp, philo->id);
	if (status == FORK)
		printf(MSG_FORK, timestamp, philo->id);
	if (status == EAT)
		printf(MSG_EAT, timestamp, philo->id);
	if (status == SLEEP)
		printf(MSG_SLEEP, timestamp, philo->id);
	if (status == THINK)
		printf(MSG_THINK, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (NULL);
}
