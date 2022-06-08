/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/08 12:15:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wipe_all(t_info *info)
{
	pthread_mutex_lock(&info->reaper->scythe);
	info->is_dead = 1;
	pthread_mutex_unlock(&info->reaper->scythe);
}

unsigned long long	get_now_reaper(t_info *info)
{
	unsigned long long	now;

	gettimeofday(&info->get_time, NULL);
	now = ((info->get_time.tv_sec - 1 - info->start_time.tv_sec) * 1000000) + \
			1000000 + (info->get_time.tv_usec - info->start_time.tv_usec);
	now = now / 1000;
	return (now);
}

void	set_last_eat(t_philo *philo, t_reaper *reaper)
{
	pthread_mutex_lock(&reaper->scythe);
	philo->nb_eat++;
	philo->last_time_eat = get_now(philo);
	pthread_mutex_unlock(&reaper->scythe);
}

unsigned long long	get_last_eat(t_philo *philo, t_reaper *reaper)
{
	unsigned long long	ret;

	pthread_mutex_lock(&reaper->scythe);
	ret = philo->last_time_eat;
	pthread_mutex_unlock(&reaper->scythe);
	return (ret);
}

void	*reaper(void *start)
{
	t_reaper	*reaper;
	int			i;

	reaper = (t_reaper *)start;
	i = 0;
	while (1)
	{
		if (have_all_eat(reaper->info, reaper) == 0)
			return (wipe_all(reaper->info), NULL);
		if (get_now_reaper(reaper->info) - \
				get_last_eat(reaper->info->philo[i], reaper) > \
				(unsigned long long)reaper->info->time_to_die)
		{
			sleeping(1);
			ft_putstr("has died\n", reaper->info->philo[i]);
			wipe_all(reaper->info);
			return (reaper);
		}
		if (is_dead(reaper->info->philo[i], reaper) == 1)
			break ;
		i++;
		if (i >= reaper->info->nb_philo)
			i = 0;
	}
	return (NULL);
}
