/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:32:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 14:33:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

typedef enum s_status
{
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_status;

void	*print_status(t_philo *philo, bool last, t_status status);

#endif