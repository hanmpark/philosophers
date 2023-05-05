/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:31:31 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:38:23 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_TOOLS_H
# define TABLE_TOOLS_H

# include <limits.h>

bool	valid_input(int argc, char **argv);
int		philo_atoi(char *arg);
void	clean_table(t_table *table);
t_table	*prepare_table(int argc, char **argv);

#endif