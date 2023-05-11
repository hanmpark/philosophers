/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:01:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 14:40:56 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "status.h"
#include "timer.h"
#include <stdio.h>

/* Prints the status for philosophers:
* - if the simulation has ended, it does not print anything
* - except for the DEAD status, it prints it anyway
*/
void	*print_status(t_philo *philo, bool last, t_status status)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (end_simulation(philo->table) == true && last == false)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (NULL);
	}
	timestamp = give_current_time() - philo->table->tm_start;
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
	pthread_mutex_unlock(&philo->table->print_lock);
	return (NULL);
}
