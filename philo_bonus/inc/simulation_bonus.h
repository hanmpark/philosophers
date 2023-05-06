/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/06 17:08:18 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdbool.h>

typedef struct s_philo
{
	unsigned int	id;
	int				times_eat;
	time_t			last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	unsigned int	number_of_philo;
	int				number_of_meals;
	bool			end_sim;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	sem_t			fork;
	struct s_philo	*philo;
}	t_table;

#endif