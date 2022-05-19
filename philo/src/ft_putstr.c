/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:51:13 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 14:13:00 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_putstr(char *str, t_philo *philo)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	pthread_mutex_lock(philo->writing);
	if (is_dead(philo, *philo->reaper) == 1)
	{
		pthread_mutex_unlock(philo->writing);
		return (1);
	}
	ft_putnbr(get_now(philo));
	write(1, " ", 1);
	ft_putnbr((unsigned long long)philo->nb);
	write(1, " ", 1);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	pthread_mutex_unlock(philo->writing);
	return (0);
}
