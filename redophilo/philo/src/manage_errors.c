/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:23:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 13:05:10 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	bool_error(const char *message, void *fork, void *philo)
{
	if (fork)
		free(fork);
	if (philo)
		free(philo);
	while (*message)
		write(2, &*message++, sizeof(char));
	return (false);
}

void	*pointer_error(const char *message)
{
	while (*message)
		write(2, &*message++, sizeof(char));
	return (NULL);
}
