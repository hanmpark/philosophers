/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:32:52 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:30:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	time_t			last_meal;
	int				id;
	int				times_ate;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nbr_philo;
	int				nbr_meals;
	bool			end_sim;
	time_t			tm_start;
	time_t			tm_starve;
	time_t			tm_eat;
	time_t			tm_sleep;
	pthread_t		watcher;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	**fork;
	struct s_philo	**philo;
}	t_table;

t_table	*init_table(int argc, char **argv);
int		philo_atoi(char *arg);
bool	check_arguments(int argc, char **argv);
bool	init_global_mutexes(t_table *table);
bool	init_philosophers(t_table *table);

bool	start_simulation(t_table *table);
void	end_simulation(t_table *table);
void	*launch_routine(void *arg);

void	*watcher(void *arg);
void	set_sim_state(t_table *table, bool state);
bool	check_sim_state(t_table *table);
void	clean_table(t_table *table, bool mutex);

#endif