/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 12:38:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_this_philo(t_info *info, t_philo *philo, int nb)
{
	philo->info = info;
	philo->nb_eat = 0;
	philo->last_time_eat = 0;
	philo->nb = nb;
}

unsigned long long	get_now(t_info *info)
{
	unsigned long long now;

	gettimeofday(&info->get_time, NULL);
	now = ((info->get_time.tv_sec - 1 - info->start_time.tv_sec) * 1000000) + 1000000 + (info->get_time.tv_usec - info->start_time.tv_usec);
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
	printf("%llu %d is sleeping\n", get_now(philo->info), philo->nb);
	sleeping(philo->info->time_to_sleep);
	printf("%llu %d is thinking\n", get_now(philo->info), philo->nb);
	take_fork(philo);
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

void	eating(t_philo *philo)
{
	printf("%llu %d is eating\n", get_now(philo->info), philo->nb);
	sleeping(philo->info->time_to_eat);
	unlock_fork(philo);
	is_sleeping(philo);
}

void	take_fork(t_philo *philo)
{
	if (philo->nb != philo->info->nb_philo)
	{
		if (philo->nb % 2 == 0)
		{
			pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
			pthread_mutex_lock(philo->info->fork[philo->nb]);
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		}
		else
		{
			pthread_mutex_lock(philo->info->fork[philo->nb]);
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
			pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		}
	}
	else
	{
		pthread_mutex_lock(philo->info->fork[0]);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
	}
	eating(philo);
}

void	*start_routine(void *start)
{
	t_philo	*philo;

	philo = (t_philo *)start;
	take_fork(philo);
	return (philo);
}
