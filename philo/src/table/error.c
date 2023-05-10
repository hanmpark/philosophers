/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:27:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/10 15:53:37 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "errors.h"
#include <unistd.h>

void	putstr_error(char *message)
{
	while (*message)
		write(2, &*message++, sizeof(char));
}

bool	msg_error(char *message, t_table *table, int nbr_lock, int nbr_fork)
{
	clean_table(table, nbr_lock, nbr_fork);
	putstr_error(message);
	return (false);
}
