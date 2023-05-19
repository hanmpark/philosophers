/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:09:11 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/19 09:22:10 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_BONUS_H
# define ERRORS_BONUS_H

# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_FORMAT "Error: Arguments are not properly formatted\n"
# define ERR_PHILO "Error: A problem occurred while initializing philos\n"
# define ERR_FORKS "Error: A problem occurred while initializing forks\n"
# define ERR_THREAD "Error: A problem occurred while creating threads\n"
# define ERR_SEM "Error: A problem occurred while initializing semaphores\n"
# define HELP "\nHELP:\n./philo_bonus number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

bool	init_error(char *msg, t_table *table, bool semaphore);

#endif