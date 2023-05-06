/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_tools_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:18:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/06 17:20:24 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_TOOLS_BONUS_H
# define TABLE_TOOLS_BONUS_H

#include <limits.h>

bool	valid_input(int argc, char **argv);
int		philo_atoi(char *arg);
void	clean_table(t_table *table);
t_table	*prepare_table(int argc, char **argv);

#endif