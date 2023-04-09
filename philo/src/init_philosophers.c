/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:55:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/09 16:57:13 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	set_philo(t_philo *philo, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philo[i].fork = 0;
		philo[i].sleep = 0;
		philo[i].think = 0;
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	if (data->nbr_philo < 1)
		ft_error(ERR_PHILO);
	data->philo = malloc((data->nbr_philo) * sizeof(t_philo));
	if (data->philo == NULL)
		ft_error(ERR_MALLOC);
	set_philo(data->philo, data->nbr_philo);
}
