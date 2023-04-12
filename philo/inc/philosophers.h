/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/12 18:42:02 by hanmpark         ###   ########.fr       */
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

# define ALIVE 1
# define DEAD 0

typedef struct s_philo
{
	pthread_mutex_t	*state;
	pthread_t		*thread;
	int				id;
	int				state;
	long long int	last_eat;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	t_philo			*philo;
	int				nbr_philo;
	int				nbr_eat;
	int				end;
	int				tm_death;
	int				tm_dine;
	int				tm_sleep;
}	t_table;

int		ft_atoi(char *str);
void	init_dining(t_table *data);
void	*philosopher_routine(void *arg);

long long int	actual_time(void);
void			wait_time(long long int wait);

#endif