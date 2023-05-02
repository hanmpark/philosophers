/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/02 14:24:51 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define ERR_ARGS_NBR "Error\nWrong number of arguments\n"
# define ERR_ARGS_DIGIT "Error\nArguments must only be consisted of digits\n"
# define ERR_ARGS_INCORRECT "Error\nArguments are not formatted \
for the program to work\n"
# define ERR_INIT_PHILO "Error\nA problem occurred when trying to initialize \
philosophers\n"
# define ERR_INIT_DINING "Error\nA problem occurred when trying to initialize \
the simulation\n"

# define RED "\033[38;5;197m"
# define GREEN "\033[38;5;190m"
# define YELLOW "\033[38;5;220m"
# define ORANGE "\033[38;5;208m"
# define DEF "\033[0m"

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_eat;
	pthread_mutex_t	eating;
	time_t			last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	unsigned int	number_of_philo;
	int				dine_left;
	bool			end_sim;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	pthread_t		watcher;
	pthread_mutex_t	end_sim_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_table;

typedef enum e_status
{
	DEAD,
	ALIVE,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

t_table	*prepare_table(int argc, char **argv);
bool	valid_input(int argc, char **argv);
int		philo_atoi(char *arg);

time_t	actual_time(void);
void	wait_time(time_t wait);
int		error_exit(const char *err_message, int exit_no);
bool	start_sim(t_table *table);
void	*philo_routine(t_philo *philo);
void	wait_start_time(time_t start_time);
void	*supervise_sim(t_table *table);
void	print_status(t_philo *philo, t_status status);

#endif