/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:37:35 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/25 12:50:21 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#include "status_bonus.h"
#include "timer_bonus.h"
#include <stdio.h>

/* Prints the status for philosophers:
* - if the simulation has ended, it does not print anything
*/
void	*print_status(t_philo *philo, bool last, t_status status)
{
	time_t	timestamp;

	timestamp = give_current_time() - philo->table->tm_start;
	sem_wait(philo->table->print_lock);
	if (status == DEAD)
		printf("%ld %d died\n", timestamp, philo->id);
	if (status == FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->id);
	if (status == EAT)
		printf("%ld %d is eating\n", timestamp, philo->id);
	if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, philo->id);
	if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, philo->id);
	if (last == false)
		sem_post(philo->table->print_lock);
	return (NULL);
}
