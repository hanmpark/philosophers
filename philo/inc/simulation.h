/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:32:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 15:36:37 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	time_t			last_meal;
	unsigned int	id;
	int				times_ate;
	pthread_mutex_t	philo_lock;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	unsigned int	nbr_philo;
	int				nbr_meals;
	bool			end_sim;
	time_t			tm_start;
	time_t			tm_starve;
	time_t			tm_eat;
	time_t			tm_sleep;
	pthread_t		watcher;
	pthread_mutex_t	end_sim_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}	t_table;

// INITALIZES EVERYTHING FOR THE PROGRAM TO WORK
t_table	*init_table(int argc, char **argv);
int		philo_atoi(char *arg);
bool	check_arguments(int argc, char **argv);
bool	init_global_mutexes(t_table *table);
bool	init_philosophers(t_table *table);

// ROUTINE FOR PHILOSOPHER(S)
void	*launch_routine(void *data);
void	*watcher(void *data);
bool	end_simulation(t_table *table);

// FREES AND DESTROYS ALLOCATED POINTERS AND MUTEXES
void	clean_table(t_table *table, int nbr_lock, int nbr_fork);

#endif