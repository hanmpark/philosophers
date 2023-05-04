/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:33:47 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/04 15:15:17 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_putstr_fd(const char *str, int fd)
{
	while (*str)
		write(fd, &*str++, 1);
}

int	error_exit(const char *err_message, int exit_no)
{
	ft_putstr_fd(err_message, 2);
	return (exit_no);
}

void	print_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->table->print);
	if (sim_has_ended(philo) == true)
	{
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	if (status == DEAD)
		printf(RED"%ld %d died\n"DEF, \
		actual_time() - philo->table->start_time, philo->id);
	else if (status == FORK)
		printf(GREEN"%ld %d has taken a fork\n"DEF, \
		actual_time() - philo->table->start_time, philo->id);
	else if (status == EATING)
		printf(PURPLE"%ld %d is eating\n"DEF, \
		actual_time() - philo->table->start_time, philo->id);
	else if (status == SLEEPING)
		printf(YELLOW"%ld %d is sleeping\n"DEF, \
		actual_time() - philo->table->start_time, philo->id);
	else if (status == THINKING)
		printf(ORANGE"%ld %d is thinking\n"DEF, \
		actual_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}
