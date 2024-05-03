/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual_sem_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:26:46 by hanmpark          #+#    #+#             */
/*   Updated: 2024/05/03 01:57:27 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

/**
 * @brief Calculates the length of a string.
 *
 * @param str The string to calculate the length of.
 *
 * @return Returns the length of the string.
 */
static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * @brief Calculates the number of digits in a number.
 *
 * @param number The number to calculate the number of digits of.
 *
 * @return Returns the number of digits in the number.
 */
static int	ft_nbrlen(unsigned int number)
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

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param number The number to convert to a string.
 *
 * @return Returns a string representation of the number, or NULL if there was
 * an error during the conversion.
 */
static char	*ft_utoa(unsigned int number)
{
	char	*number_str;
	int		len;

	len = ft_nbrlen(number);
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

/**
 * @brief Concatenates two strings.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 *
 * @return Returns a new string that is the concatenation of s1 and s2, or NULL
 * if there was an error during the concatenation.
 */
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

/**
 * @brief Creates a unique name for an individual semaphore.
 *
 * @param name The base name for the semaphore.
 * @param number The number to append to the base name to create a unique name.
 *
 * @return Returns a unique name for an individual semaphore, or NULL if there
 * was an error during the creation of the name.
 */
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
