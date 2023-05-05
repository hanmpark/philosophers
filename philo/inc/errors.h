/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:22:09 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:23:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGS_NBR "Error: Wrong number of arguments\n"
# define ERR_INIT_PHILO "Error: A problem occurred when trying to initialize \
philosophers\n"
# define ERR_INIT_SIM "Error: A problem occurred when trying to initialize \
the simulation\n"
# define HELP "\nHELP:\n./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

int	error_exit(const char *err_message);

#endif