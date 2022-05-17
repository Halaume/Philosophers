/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 15:00:51 by ghanquer         ###   ########.fr       */
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

int	is_dead(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo && info->philo[i])
	{
		if (info->philo[i]->is_dead == 1)
			return (1);
	}
	return (0);
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

void	eating(t_philo *philo)
{
	if (is_dead(philo->info) == 1)
		return ;
	printf("%llu %d is eating\n", get_now(philo->info), philo->nb);
	philo->last_time_eat = get_now(philo->info);
	sleeping(philo->info->time_to_eat);
	unlock_fork(philo);
	is_sleeping(philo);
}

void	take_fork(t_philo *philo)
{
	if (is_dead(philo->info) == 1)
		return ;
	if (philo->nb != philo->info->nb_philo)
	{
		if (philo->nb % 2 == 0)
		{
			pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
			if (is_dead(philo->info) == 1)
				return ;
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
			pthread_mutex_lock(philo->info->fork[philo->nb]);
			if (is_dead(philo->info) == 1)
				return ;
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		}
		else
		{
			pthread_mutex_lock(philo->info->fork[philo->nb]);
			if (is_dead(philo->info) == 1)
				return ;
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
			pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
			if (is_dead(philo->info) == 1)
				return ;
			printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		}
	}
	else
	{
		pthread_mutex_lock(philo->info->fork[0]);
		if (is_dead(philo->info) == 1)
			return ;
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
		if (is_dead(philo->info) == 1)
			return ;
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
	}
	eating(philo);
}

void	*start_routine(void *start)
{
	t_philo	*philo;

	philo = (t_philo *)start;
	while (1)
	{
		if (is_dead(philo->info) == 1)
			break ;
		take_fork(philo);
	}
	return (philo);
}

void	wipe_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		info->philo[i]->is_dead = 1;
}

void	*reaper(void *start)
{
	t_reaper	*reaper;
	int			i;

	reaper = (t_reaper *)start;
	i = 0;
	while (1)
	{
		if (get_now(reaper->info) - reaper->info->philo[i]->last_time_eat > (unsigned long long)reaper->info->time_to_die)
		{
			printf("%llu %d has died\n", get_now(reaper->info), reaper->info->philo[i]->nb);
			wipe_all(reaper->info);
			return (reaper);
		}
		i++;
		if (i >= reaper->info->nb_philo)
			i = 0;
	}
	return (reaper);
}
