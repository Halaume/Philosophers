/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:53:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/09 11:50:24 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *philo, t_reaper *reaper)
{
	pthread_mutex_lock(&reaper->scythe);
	if (philo->is_dead[0] == 1 || have_all_eat(reaper->info) == 0)
		return (pthread_mutex_unlock(&reaper->scythe), 1);
	pthread_mutex_unlock(&reaper->scythe);
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

int	malloc_all(t_info *info)
{
	int	i;

	i = -1;
	info->is_dead = 0;
	info->thread_philo = malloc(sizeof(pthread_t *) * info->nb_philo);
	info->fork = malloc(sizeof(pthread_mutex_t *) * info->nb_philo);
	info->philo = malloc(sizeof(t_philo *) * info->nb_philo);
	if (!info->fork || !info->thread_philo || !info->philo || !info->nb_philo)
		return (free_fun(info), 1);
	while (++i < info->nb_philo)
	{
		info->fork[i] = malloc(sizeof(pthread_mutex_t) * 1);
		info->thread_philo[i] = malloc(sizeof(pthread_t) * 1);
		info->philo[i] = malloc(sizeof(t_philo) * 1);
		if (!info->fork[i] || !info->thread_philo[i] || !info->philo[i])
			return (free_fun(info), 1);
		init_this_philo(info, info->philo[i], i + 1);
		if (pthread_mutex_init(info->fork[i], NULL) != 0)
			return (free_fun(info), 1);
	}
	if (init_reaper(info) == 1)
		return (1);
	return (0);
}

void	set_last_eat(t_philo *philo, t_reaper *reaper)
{
	pthread_mutex_lock(&reaper->scythe);
	philo->last_time_eat = get_now(philo);
	philo->nb_eat++;
	pthread_mutex_unlock(&reaper->scythe);
}

unsigned long long	get_last_eat(t_philo *philo)
{
	unsigned long long	ret;

	ret = philo->last_time_eat;
	return (ret);
}
