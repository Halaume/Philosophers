/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 11:12:52 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
		return ;
	ft_putstr("is eating\n", philo);
	philo->nb_eat++;
	philo->last_time_eat = get_now(philo);
	sleeping(philo->time_to_eat);
	unlock_fork(philo);
	is_sleeping(philo);
}

int	took_fork(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_lock[0][philo->nb - 1] = 1;
		if (is_dead(philo, *philo->reaper) == 1)
			return (1);
		ft_putstr("has taken a fork\n", philo);
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_lock[0][philo->nb] = 1;
		if (is_dead(philo, *philo->reaper) == 1)
			return (1);
		ft_putstr("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_lock[0][philo->nb] = 1;
		if (is_dead(philo, *philo->reaper) == 1)
			return (pthread_mutex_unlock(philo->fork[0][philo->nb]), 1);
		ft_putstr("has taken a fork\n", philo);
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_lock[0][philo->nb - 1] = 1;
		if (is_dead(philo, *philo->reaper) == 1)
			return (pthread_mutex_lock(philo->fork[0][philo->nb - 1]), 1);
		ft_putstr("has taken a fork\n", philo);
	}
	return (0);
}

void	take_fork(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
		return ;
	if (philo->nb != philo->nb_philo)
	{
		if (took_fork(philo) == 1)
			return ;
	}
	else
	{
		pthread_mutex_lock(philo->fork[0][0]);
		if (is_dead(philo, *philo->reaper) == 1)
		{
			pthread_mutex_unlock(philo->fork[0][0]);
			return ;
		}
		ft_putstr("has taken a fork\n", philo);
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		if (is_dead(philo, *philo->reaper) == 1)
		{
			pthread_mutex_unlock(philo->fork[0][philo->nb - 1]);
			return ;
		}
		ft_putstr("has taken a fork\n", philo);
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
	return (philo);
}
