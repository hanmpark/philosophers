/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:33:58 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/11 15:41:11 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_FORMAT "Error: Arguments are not properly formatted\n"
# define ERR_PHILO "Error: A problem occurred while initializing philos\n"
# define ERR_FORKS "Error: A problem occurred while initializing forks\n"
# define ERR_MUTEX "Error: A problem occurred while initializing a mutex\n"
# define ERR_THREAD "Error: A problem occurred while creating threads\n"

bool	table_error(char *msg, t_table *table, int nbr_lock, int nbr_fork);
bool	thread_error(char *msg, t_table *table, int nbr_thread);

#endif