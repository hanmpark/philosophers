/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:33:47 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:45:17 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "print_status.h"
#include "errors.h"

static void	ft_putstr_fd(const char *str, int fd)
{
	while (*str)
		write(fd, &*str++, 1);
}

// Prints the error message and the helper and returns EXIT_FAILURE
int	error_exit(const char *err_message)
{
	ft_putstr_fd(err_message, 2);
	ft_putstr_fd(HELP, 2);
	return (EXIT_FAILURE);
}

// Prints one philosopher's status with its timestamp
void	print_status(t_philo *philo, bool last_announcement, t_status status)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->table->print);
	if (sim_has_ended(philo) == true && last_announcement == false)
	{
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	timestamp = actual_time() - philo->table->start_time;
	if (status == DEAD)
		printf(RED"%ld %d died\n"DEF, timestamp, philo->id);
	else if (status == FORK)
		printf(GREEN"%ld %d has taken a fork\n"DEF, timestamp, philo->id);
	else if (status == EATING)
		printf(PURPLE"%ld %d is eating\n"DEF, timestamp, philo->id);
	else if (status == SLEEPING)
		printf(YELLOW"%ld %d is sleeping\n"DEF, timestamp, philo->id);
	else if (status == THINKING)
		printf(ORANGE"%ld %d is thinking\n"DEF, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}
