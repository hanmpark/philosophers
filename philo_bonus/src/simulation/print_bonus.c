/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:37:35 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 13:59:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"
#include <stdio.h>

void	*print_status(t_philo *philo, bool last, t_status status)
{
	time_t	timestamp;

	timestamp = give_current_time() - philo->table->tm_start;
	sem_wait(philo->table->print_lock);
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
	if (last == false)
		sem_post(philo->table->print_lock);
	return (NULL);
}
