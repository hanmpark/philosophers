/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:33:47 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/13 16:56:05 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_putstr_fd(const char *str, int fd)
{
	while (*str)
		write(fd, *str++, 1);
}

int	error_exit(const char *err_message, int exit_no)
{
	ft_putstr_fd(err_message, 2);
	return (exit_no);
}

long long int	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_time(long long int wait)
{
	long long int	timemark;

	timemark = actual_time();
	while (actual_time() - timemark < wait)
		usleep(100);
}

