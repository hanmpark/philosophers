/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:33:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/11 16:20:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.c"

void	*philosopher_routine(void *arg)
{
	t_data	*data;
	int	left_fork;
	int	right_fork;

	data = (t_data *)arg;
	left_fork = *data->id;
	right_fork = (*data->id + 1) % data->nbr_philo;
}