/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:51:13 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/09 11:50:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int	ft_putstr(char *str, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(philo->writing);
	if (!str || !*str)
		return (pthread_mutex_unlock(philo->writing), 1);
	if (is_dead(philo, *philo->reaper) == 1)
		return (pthread_mutex_unlock(philo->writing), 1);
	if (ft_strcmp("has died\n", str) == 0 && \
			is_it_dead(*philo->reaper, philo) == 0)
		return (pthread_mutex_unlock(philo->writing), 1);
	ft_putnbr(get_now(philo));
	write(1, " ", 1);
	ft_putnbr((unsigned long long)philo->nb);
	write(1, " ", 1);
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	pthread_mutex_unlock(philo->writing);
	return (0);
}
