/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:38:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 15:28:35 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

# include <sys/time.h>
# include <unistd.h>

time_t	current_time(void);
void	wait_until_start(time_t time);
void	*philo_wait(t_table *table, t_status status);

#endif