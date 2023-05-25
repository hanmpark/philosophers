/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/25 20:08:16 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	unsigned int	id;
	pid_t			pid;
	time_t			last_meal;
	int				count_meal;
	char			*nm_lock;
	sem_t			*meal_lock;
	pthread_t		watcher;
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
	sem_t			*fork_lock;
	sem_t			*print_lock;
	sem_t			*sim_lock;
	sem_t			*ate_enough;
	pthread_t		limiter;
	struct s_philo	*philo;
}	t_table;

/* INITIALIZATION */
bool	check_arguments(int argc, char **argv);
int		philo_atoi(char *arg);
t_table	*init_table(int argc, char **argv);
bool	init_global_sem(t_table *table);
bool	init_philosophers(t_table *table);
char	*individual_sem_name(char *name, unsigned int number);

/* ROUTINE */
bool	start_simulation(t_table *table);
void	stop_simulation(t_table *table);
void	*launch_routine(t_philo *philo);
void	*watcher(void *data);
void	*limiter(void *arg);

/* EXIT */
bool	init_error(char *msg, t_table *table, bool semaphore);
void	kill_philosophers(t_table *table);
void	clean_table(t_table *table, bool semaphore);

#endif