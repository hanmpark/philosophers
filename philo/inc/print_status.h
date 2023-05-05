/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:25:33 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/05 16:28:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_STATUS_H
# define PRINT_STATUS_H

# include <stdio.h>

# define RED "\033[38;5;197m"
# define PURPLE "\033[38;5;129m"
# define GREEN "\033[38;5;190m"
# define YELLOW "\033[38;5;220m"
# define ORANGE "\033[38;5;208m"
# define DEF "\033[0m"

typedef enum e_status
{
	DEAD,
	ALIVE,
	FORK,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

void	print_status(t_philo *philo, bool last_announcement, t_status status);

#endif