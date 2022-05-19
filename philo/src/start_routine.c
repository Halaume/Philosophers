/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 17:36:48 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
	{
		unlock_fork(philo);
		return ;
	}
	ft_putstr("is eating\n", philo);
	set_last_eat(philo, *philo->reaper);
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
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_lock[0][philo->nb] = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
	}
	else
	{
		pthread_mutex_lock(philo->fork[0][philo->nb]);
		philo->fork_lock[0][philo->nb] = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_lock[0][philo->nb - 1] = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
			return (unlock_fork(philo), 1);
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
		philo->fork_lock[0][0] = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
		{
			unlock_fork(philo);
			return ;
		}
		pthread_mutex_lock(philo->fork[0][philo->nb - 1]);
		philo->fork_lock[0][philo->nb - 1] = 1;
		if (ft_putstr("has taken a fork\n", philo) == 1)
		{
			unlock_fork(philo);
			return ;
		}
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
