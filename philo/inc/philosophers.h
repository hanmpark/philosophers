/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/11 16:49:51 by hanmpark         ###   ########.fr       */
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
# include <errno.h>

# define ERR_MALLOC "malloc()"
# define ERR_ARGS "stdin"
# define ERR_PHILO "wrong number of philosophers"

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_t		*philosopher;
	int				*id;
	int				nbr_philo;
	long long int	tm_to_die;
	long long int	tm_to_eat;
	long long int	tm_to_sleep;
	int				nbr_eat;
}	t_data;

int		ft_atoi(char *str);
void	ft_error(const char *message);
void	init_dining(t_data *data);
void	*philosopher_routine(void *arg);

#endif