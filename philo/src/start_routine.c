/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/09 11:52:16 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	took_fork(t_philo *philo)
{
	if (philo->nb % 2 != 0)
	{
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_left = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_right = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
	}
	else
	{
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_right = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_left = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
	}
	return (0);
}

int	took_last_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
	philo->fork_left = 1;
	if (ft_putstr("has taken a fork\n", philo) == 1)
	{
		unlock_fork(philo);
		return (1);
	}
	pthread_mutex_lock(philo->fork[0][0]);
	philo->fork_right = 1;
	if (ft_putstr("has taken a fork\n", philo) == 1)
	{
		unlock_fork(philo);
		return (1);
	}
	return (0);
}

int	took_last_fork(t_philo *philo)
{
	if (philo->nb % 2 != 0)
	{
		if (took_last_fork2(philo) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_lock(philo->fork[0][0]);
		philo->fork_right = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
		{
			unlock_fork(philo);
			return (1);
		}
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_left = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
		{
			unlock_fork(philo);
			return (1);
		}
	}
	return (0);
}

void	take_fork(t_philo *philo)
{
	if (philo->nb != philo->nb_philo)
	{
		if (took_fork(philo) == 1)
			return ;
	}
	else
	{
		if (took_last_fork(philo) == 1)
			return ;
	}
	eating(philo);
}

void	*start_routine(void *start)
{
	t_philo	*philo;

	philo = (t_philo *)start;
	while (1)
	{
		if (is_dead(philo, *philo->reaper) == 1)
			break ;
		take_fork(philo);
	}
	return (NULL);
}
