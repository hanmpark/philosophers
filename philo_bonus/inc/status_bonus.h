/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:23:41 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/12 13:32:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_STATUS_BONUS_H
# define PRINT_STATUS_BONUS_H

typedef enum e_status
{
	DEAD,
	FORK,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

#endif