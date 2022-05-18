/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/18 17:07:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *philo, t_reaper *reaper)
{
	int	i;

	i = -1;
	pthread_mutex_lock(reaper->scythe);
	if (*philo->is_dead == 1)
		return (pthread_mutex_unlock(reaper->scythe), 1);
	pthread_mutex_unlock(reaper->scythe);
	return (0);
}

int	have_all_eat(t_info *info)
{
	int	i;

	i = -1;
	if (info->nb_of_eat < 0)
		return (1);
	while (++i < info->nb_philo && info->philo[i])
	{
		if (info->philo[i]->nb_eat < info->nb_of_eat)
			return (1);
	}
	return (0);
}

void	wipe_all(t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_lock(info->reaper->scythe);
	info->is_dead = 1;
	while (++i < info->nb_philo)
	{
		unlock_fork(info->philo[i]);
	}
	pthread_mutex_unlock(info->reaper->scythe);
}

unsigned long long get_now_reaper(t_info *info)
{
	unsigned long long	now;

	gettimeofday(&info->get_time, NULL);
	now = ((info->get_time.tv_sec - 1 - info->start_time.tv_sec) * 1000000) + \
			1000000 + (info->get_time.tv_usec - info->start_time.tv_usec);
	now = now / 1000;
	return (now);
}

void	*reaper(void *start)
{
	t_reaper	*reaper;
	int			i;

	reaper = (t_reaper *)start;
	i = 0;
	while (1)
	{
		if (have_all_eat(reaper->info))
			return (reaper);
		if (get_now_reaper(reaper->info) - \
				reaper->info->philo[i]->last_time_eat > \
				(unsigned long long)reaper->info->time_to_die)
		{
			printf("%llu %d has died\n", get_now_reaper(reaper->info), \
					reaper->info->philo[i]->nb);
			wipe_all(reaper->info);
			return (reaper);
		}
		if (reaper->info->is_dead == 1)
			break ;
		i++;
		if (i >= reaper->info->nb_philo)
			i = 0;
	}
	return (reaper);
}
