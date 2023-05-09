/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 13:58:29 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	int				times_eat;
	time_t			last_eat;
	pthread_mutex_t	meal_lock;
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
	pthread_t		watcher;
	pthread_mutex_t	end_sim_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}	t_table;

/* time related functions */
time_t	actual_time(void);
void	wait_time(time_t wait);

/* simulation management */
bool	start_sim(t_table *table);
bool	stop_sim(t_table *table);
bool	sim_has_ended(t_philo *philo);

/* routines */
void	*launch_routine(void *arg);
void	*lonely_routine(void *arg);
void	*watcher(void *arg);


#endif