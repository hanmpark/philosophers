/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:23:41 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/30 16:44:59 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_BONUS_H
# define STATUS_BONUS_H

typedef enum e_status
{
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_status;

void	*print_status(t_philo *philo, bool last, t_status status);

#endif