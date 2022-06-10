/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/10 10:59:50 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wipe_all(t_info *info)
{
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

int	is_it_dead(t_reaper *reaper, t_philo *philo)
{
	if (get_now_reaper(reaper->info) - \
			get_last_eat(philo) > \
			(unsigned long long)reaper->info->time_to_die)
		return (1);
	return (0);
}

void	*my_while(t_reaper *reaper, int i)
{
	while (1)
	{
		pthread_mutex_lock(&reaper->scythe);
		if (have_all_eat(reaper->info) == 0)
			return (wipe_all(reaper->info), NULL);
		if (is_it_dead(reaper, reaper->info->philo[i]))
		{
			pthread_mutex_unlock(&reaper->scythe);
			sleeping(1);
			if (ft_putstr("has died\n", reaper->info->philo[i]) != 1)
			{
				pthread_mutex_lock(&reaper->scythe);
				reaper->info->is_dead = 1;
				return (pthread_mutex_unlock(&reaper->scythe), reaper);
			}
		}
		pthread_mutex_unlock(&reaper->scythe);
		if (is_dead(reaper->info->philo[i], reaper) == 1)
			break ;
		i++;
		if (i >= reaper->info->nb_philo)
			i = 0;
	}
	return (NULL);
}

void	*reaper(void *start)
{
	t_reaper	*reaper;

	reaper = (t_reaper *)start;
	my_while(reaper, 0);
	return (NULL);
}
