/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:51:13 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 11:09:09 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putstr(char *str, t_philo *philo)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	pthread_mutex_lock(philo->writing);
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
}
