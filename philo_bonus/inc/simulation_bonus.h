/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/20 16:36:38 by hanmpark         ###   ########.fr       */
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
	time_t			last_meal;
	pid_t			pid;
	unsigned int	id;
	int				times_ate;
	pthread_t		hunger_watcher;
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
	sem_t			*fork_sem;
	sem_t			*print_sem;
	sem_t			*sim_sem;
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

/* ROUTINE */
bool	start_simulation(t_table *table);
void	stop_simulation(t_table *table);
void	*launch_routine(t_philo *philo);
void	*hunger_watcher(void *data);
void	*limiter(void *arg);

/* EXIT */
bool	init_error(char *msg, t_table *table, bool semaphore);
void	kill_philosophers(t_table *table);
void	clean_table(t_table *table, bool semaphore);

#endif