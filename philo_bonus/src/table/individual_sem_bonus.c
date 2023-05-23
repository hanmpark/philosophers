/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_sem_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:26:46 by hanmpark          #+#    #+#             */
/*   Updated: 2023/05/23 13:02:48 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	nbrlen(unsigned int number)
{
	int	len;

	len = 0;
	while (number)
	{
		number /= 10;
		len++;
	}
	return (len);
}

static char	*ft_utoa(unsigned int number)
{
	char	*number_str;
	int		len;

	len = nbrlen(number);
	number_str = malloc((len + 1) * sizeof(char));
	if (!number_str)
		return (NULL);
	number_str[len] = 0;
	while (len-- > 0)
	{
		number_str[len] = number % 10 + '0';
		number /= 10;
	}
	return (number_str);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i++] = s2[j];
	join[i] = 0;
	return (join);
}

char	*individual_sem_name(char *name, unsigned int number)
{
	char	*nbrstr;
	char	*nm_semaphore;

	nbrstr = ft_utoa(number);
	if (!nbrstr)
		return (NULL);
	nm_semaphore = ft_strjoin(name, nbrstr);
	free(nbrstr);
	if (!nm_semaphore)
		return (NULL);
	return (nm_semaphore);
}
