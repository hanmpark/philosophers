/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:32:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/09 14:23:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

# define ERR_ARGS "Wrong number of arguments\n"
# define ERR_FORMAT "Arguments are not properly formatted\n"

# define ERR_FORKS "A problem occurred while initializing forks\n"
# define ERR_MUTEX "A problem occurred while initializing a mutex\n"

# define ERR_PHILO "A problem occurred while initializing philosophers\n"

typedef struct s_philo
{
	pthread_t		thread; // ok
	time_t			last_meal; // ok
	unsigned int	id; // ok
	int				times_ate; // ok
	pthread_mutex_t	philo_lock; // ok
	struct s_table	*table; // ok
}	t_philo;

typedef struct s_table
{
	unsigned int	nbr_philo; // ok
	int				nbr_meals; // ok
	bool			end_sim; // ok
	time_t			tm_start; // ok
	time_t			tm_starve; // ok
	time_t			tm_eat; // ok
	time_t			tm_sleep; // ok
	pthread_t		watcher; // ok
	pthread_mutex_t	end_sim_lock; // ok
	pthread_mutex_t	print; // ok
	pthread_mutex_t	*fork; // ok
	struct s_philo	*philo; // ok
}	t_table;

typedef enum s_status
{
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_status;

t_table	*init_table(int argc, char **argv);
bool	bool_error(const char *message, void *fork, void *philo);
void	*pointer_error(const char *message);

int		philo_atoi(char *arg);
bool	check_arguments(int argc, char **argv);

bool	init_global_mutexes(t_table *table);

bool	init_philosophers(t_table *table);

time_t	give_actual_time(void);
void	wait_until_start(time_t start);
void	*philo_wait(t_table *table, t_status status);

void	*launch_routine(void *data);
void	*watcher(void *data);

bool	end_simulation(t_table *table);
void	*print_status(t_philo *philo, bool last, t_status status);

#endif