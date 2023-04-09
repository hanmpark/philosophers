/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:15:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/04/09 21:40:26 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <stdbool.h>
# include <errno.h>

# define ERR_MALLOC "malloc()"
# define ERR_ARGS "stdin"
# define ERR_PHILO "wrong number of philosophers"

typedef struct s_philo
{
	int	sleep;
	int	think;
}	t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;
}	t_data;

void	init_philosophers(t_data *data);
int		ft_atoi(char *str);
void	ft_error(const char *message);

#endif