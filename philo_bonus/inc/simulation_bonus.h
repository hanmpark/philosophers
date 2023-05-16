/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:58:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/16 19:01:58 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	time_t			last_meal;
	pid_t			pid;
	unsigned int	id;
	int				times_ate;
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
	sem_t			fork_sem;
	sem_t			print_sem;
	sem_t			sim_sem;
	struct s_philo	*philo;
}	t_table;

bool	init_philosophers(t_table *table);
void	*launch_routine(t_philo *philo);

#endif