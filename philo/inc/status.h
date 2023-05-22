/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:32:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/22 23:30:29 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# define MSG_DEAD "%ld %d died\n"
# define MSG_FORK "%ld %d has taken a fork\n"
# define MSG_EAT "%ld %d is eating\n"
# define MSG_SLEEP "%ld %d is sleeping\n"
# define MSG_THINK "%ld %d is thinking\n"

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