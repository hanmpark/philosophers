/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/12 15:06:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		watcher;
	time_t			last_meal;
	unsigned int	id;
	int				times_ate;
	sem_t			times_sem;
	sem_t			meal_sem;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	unsigned int	nbr_philo;
	int				nbr_meals;
	bool			end_sim;
	time_t			start_time;
	time_t			tm_starve;
	time_t			tm_eat;
	time_t			tm_sleep;
	sem_t			fork_sem;
	sem_t			print_sem;
	sem_t			sim_sem;
	struct s_philo	*philo;
}	t_table;

#endif