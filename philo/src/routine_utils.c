/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:08:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/08 12:40:21 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	unlock_basic1(t_philo *philo)
{
	if (philo->fork_left == 1)
	{
		philo->fork_left = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb - 1]);
	}
	if (philo->fork_right == 1)
	{
		philo->fork_right = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb]);
	}
}

void	unlock_basic2(t_philo *philo)
{
	if (philo->fork_right == 1)
	{
		philo->fork_right = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb]);
	}
	if (philo->fork_left == 1)
	{
		philo->fork_left = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb - 1]);
	}
}

void	unlock_last1(t_philo *philo)
{
	if (philo->fork_left == 1)
	{
		philo->fork_left = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb - 1]);
	}
	if (philo->fork_right == 1)
	{
		philo->fork_right = 0;
		pthread_mutex_unlock(philo->fork[0][0]);
	}
}

void	unlock_last2(t_philo *philo)
{
	if (philo->fork_right == 1)
	{
		philo->fork_right = 0;
		pthread_mutex_unlock(philo->fork[0][0]);
	}
	if (philo->fork_left == 1)
	{
		philo->fork_left = 0;
		pthread_mutex_unlock(philo->fork[0][philo->nb - 1]);
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->nb != philo->nb_philo && philo->nb % 2 != 0)
		unlock_basic1(philo);
	if (philo->nb != philo->nb_philo && philo->nb % 2 == 0)
		unlock_basic2(philo);
	else if (philo->nb % 2 != 0)
		unlock_last1(philo);
	else
		unlock_last2(philo);
}
