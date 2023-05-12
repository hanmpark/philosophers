/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:18:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/12 14:53:11 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_TOOLS_BONUS_H
# define TABLE_TOOLS_BONUS_H

#include <limits.h>

bool	valid_input(int argc, char **argv);
int		philo_atoi(char *arg);
void	clean_table(t_table *table, bool semaphore);
t_table	*init_table(int argc, char **argv);

#endif