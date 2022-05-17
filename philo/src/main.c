/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 17:46:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	malloc_all(t_info *info)
{
	int	i;

	i = 0;
	info->thread_philo = malloc(sizeof(pthread_t *) * info->nb_philo);
	info->fork = malloc(sizeof(pthread_mutex_t *) * info->nb_philo);
	info->philo = malloc(sizeof(t_philo *) * info->nb_philo);
	if (!info->fork || !info->thread_philo || !info->philo)
		return (free_fun(info), 1);
	while (i < info->nb_philo)
	{
		info->fork[i] = malloc(sizeof(pthread_mutex_t) * 1);
		info->thread_philo[i] = malloc(sizeof(pthread_t) * 1);
		info->philo[i] = malloc(sizeof(t_philo) * 1);
		if (!info->fork[i] || !info->thread_philo[i] || !info->philo[i])
			return (free_fun(info), 1);
		init_this_philo(info, info->philo[i], i + 1);
		if (pthread_mutex_init(info->fork[i], NULL) != 0)
			return (free_fun(info), 1);
		i++;
	}
	return (0);
}

int	init_muthread(t_info *info)
{
	int	i;

	i = 0;
	if (malloc_all(info) == 1)
		return (1);
	while (i < info->nb_philo)
	{
		if (pthread_create(info->thread_philo[i], NULL, start_routine, \
					info->philo[i]) != 0)
			return (free_fun(info), 1);
		i++;
	}
	return (0);
}

int	init_reaper(t_reaper *reaperz, t_info *info)
{
	reaperz->info = info;
	if (pthread_create(&reaperz->my_reaper, NULL, reaper, reaperz) != 0)
		return (free_fun(info), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	int			i;
	t_reaper	reaper;

	i = -1;
	if (check_arg(argc, argv, &info) == 1)
		return (1);
	if (init_muthread(&info) == 1)
		return (1);
	if (init_reaper(&reaper, &info) == 1)
		return (1);
	while (++i < info.nb_philo)
		pthread_join(*info.thread_philo[i], NULL);
	pthread_join(reaper.my_reaper, NULL);
	free_fun(&info);
	return (0);
}
