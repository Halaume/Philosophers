/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:08:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/18 16:57:37 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_this_philo(t_info *info, t_philo *philo, int nb)
{
	philo->nb_eat = 0;
	philo->last_time_eat = 0;
	philo->nb = nb;
	philo->start = info->start_time;
	philo->is_dead = &info->is_dead;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->fork_lock = &info->fork_lock;
	philo->reaper = &info->reaper;
	philo->nb_philo = info->nb_philo;
	philo->fork = &info->fork;
	philo->nb_of_eat = info->nb_of_eat;
}

unsigned long long	get_now(t_philo *philo)
{
	unsigned long long	now;

	gettimeofday(&philo->get_time, NULL);
	now = ((philo->get_time.tv_sec - 1 - philo->start.tv_sec) * 1000000) + \
			1000000 + (philo->get_time.tv_usec - philo->start.tv_usec);
	now = now / 1000;
	return (now);
}

void	sleeping(useconds_t time)
{
	time = time * 1000;
	while (time > 99999)
	{
		usleep(100000);
		time -= 100000;
	}
	usleep(time);
}

void	is_sleeping(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
		return ;
	printf("%llu %d is sleeping\n", get_now(philo), philo->nb);
	sleeping(philo->time_to_sleep);
	if (*philo->is_dead == 1)
		return ;
	printf("%llu %d is thinking\n", get_now(philo), philo->nb);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->nb != philo->nb_philo)
	{
		if (*philo->fork_lock[philo->nb - 1] == 1)
		{
			pthread_mutex_unlock(*philo->fork[philo->nb - 1]);
			philo->fork_lock[philo->nb - 1] = 0;
		}
		if (*philo->fork_lock[philo->nb] == 1)
		{
			pthread_mutex_unlock(*philo->fork[philo->nb]);
			*philo->fork_lock[philo->nb] = 0;
		}
	}
	else
	{
		if (*philo->fork_lock[0] == 1)
		{
			pthread_mutex_unlock(*philo->fork[0]);
			*philo->fork_lock[0] = 0;
		}
		if (*philo->fork_lock[philo->nb - 1] == 1)
		{
			pthread_mutex_unlock(*philo->fork[philo->nb - 1]);
			*philo->fork_lock[philo->nb - 1] = 0;
		}
	}
}