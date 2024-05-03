/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:37:35 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 02:06:06 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"
#include <stdio.h>

/**
 * @brief Prints the status of a philosopher.
 *
 * Gets the current timestamp and waits for the print lock semaphore. Depending
 * on the status, prints the appropriate message. If the last parameter is
 * false, posts to the print lock semaphore.
 *
 * @param philo A pointer to the t_philo structure representing the philosopher.
 * @param last A boolean indicating whether this is the last status to print.
 * @param status The status of the philosopher.
 *
 * @return Returns NULL.
 */
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
