/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:18:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 14:15:02 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_BONUS_H
# define TIMER_BONUS_H

# include <sys/time.h>
# include <unistd.h>

time_t	give_current_time(void);
void	*philo_wait(time_t wait_time);

#endif