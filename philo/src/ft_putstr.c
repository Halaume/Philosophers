/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:51:13 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/20 11:51:36 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_putstr(char *str, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(philo->writing);
	if (!str || !*str)
		return (pthread_mutex_unlock(philo->writing), 1);
	if (is_dead(philo, *philo->reaper) == 1)
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
