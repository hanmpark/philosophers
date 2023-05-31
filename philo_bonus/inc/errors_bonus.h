/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:09:11 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/31 14:09:38 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_BONUS_H
# define ERRORS_BONUS_H

# define ERR_ARGS "Error: Wrong number of arguments\n\n"
# define ERR_FORMAT "Error: Arguments are not properly formatted\n\n"
# define ERR_PHILO "Error: A problem occurred while initializing philos\n\n"
# define ERR_FORKS "Error: A problem occurred while initializing forks\n\n"
# define ERR_THREAD "Error: A problem occurred while creating threads\n\n"
# define ERR_SEM "Error: A problem occurred while initializing semaphores\n\n"
# define HELP "Helper: ./philo_bonus \
nb_philo tm_starve tm_eat tm_sleep [nb_meals]\n"

bool	init_error(char *msg, t_table *table, bool semaphore);

#endif