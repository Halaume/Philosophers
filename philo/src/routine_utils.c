/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:08:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 17:18:06 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_this_philo(t_info *info, t_philo *philo, int nb)
{
	philo->info = info;
	philo->nb_eat = 0;
	philo->last_time_eat = 0;
	philo->nb = nb;
	philo->is_dead = 0;
}

unsigned long long	get_now(t_info *info)
{
	unsigned long long	now;

	gettimeofday(&info->get_time, NULL);
	now = ((info->get_time.tv_sec - 1 - info->start_time.tv_sec) * 1000000) + \
			1000000 + (info->get_time.tv_usec - info->start_time.tv_usec);
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
	if (is_dead(philo->info) == 1)
		return ;
	printf("%llu %d is sleeping\n", get_now(philo->info), philo->nb);
	sleeping(philo->info->time_to_sleep);
	if (philo->is_dead == 1)
		return ;
	printf("%llu %d is thinking\n", get_now(philo->info), philo->nb);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->nb != philo->info->nb_philo)
	{
		pthread_mutex_unlock(philo->info->fork[philo->nb - 1]);
		pthread_mutex_unlock(philo->info->fork[philo->nb]);
	}
	else
	{
		pthread_mutex_unlock(philo->info->fork[0]);
		pthread_mutex_unlock(philo->info->fork[philo->nb - 1]);
	}
}
