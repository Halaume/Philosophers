/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/20 12:32:24 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_reaper(t_info *info)
{
	info->reaper->info = info;
	if (pthread_mutex_init(&info->reaper->scythe, NULL) != 0)
		return (free_fun(info), 1);
	if (pthread_create(&info->reaper->my_reaper, NULL, reaper, info->reaper) != 0)
		return (free_fun(info), 1);
//	pthread_detach(info->reaper->my_reaper);
	return (0);
}

int	malloc_all(t_info *info)
{
	int	i;

	i = 0;
	info->is_dead = 0;
	info->thread_philo = malloc(sizeof(pthread_t *) * info->nb_philo);
	info->fork = malloc(sizeof(pthread_mutex_t *) * info->nb_philo);
	info->philo = malloc(sizeof(t_philo *) * info->nb_philo);
	info->fork_lock = malloc(sizeof(int) * info->nb_philo);
	if (!info->fork || !info->thread_philo || !info->philo || !info->nb_philo)
		return (free_fun(info), 1);
	while (i < info->nb_philo)
	{
		info->fork_lock[i] = 0;
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
	if (init_reaper(info) == 1)
		return (1);
	return (0);
}

int	launch_it_odd(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (i % 2 == 0 && i != info->nb_philo - 1)
		{
			if (pthread_create(info->thread_philo[i], NULL, start_routine, \
						info->philo[i]) != 0)
				return (free_fun(info), 1);
		}
	}
	sleeping(info->time_to_eat / 2);
	if (pthread_create(info->thread_philo[info->nb_philo - 1], NULL, start_routine, \
				info->philo[info->nb_philo - 1]) != 0)
		return (free_fun(info), 1);
	i = -1;
	while (++i < info->nb_philo)
	{
		if (i % 2 != 0 && i != info->nb_philo - 1)
		{
			if (pthread_create(info->thread_philo[i], NULL, start_routine, \
						info->philo[i]) != 0)
				return (free_fun(info), 1);
		}
	}
	return (0);
}

int	launch_it(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(info->thread_philo[i], NULL, start_routine, \
						info->philo[i]) != 0)
				return (free_fun(info), 1);
		}
	}
	sleeping(info->time_to_eat / 2);
	i = -1;
	while (++i < info->nb_philo)
	{
		if (i % 2 != 0)
		{
			if (pthread_create(info->thread_philo[i], NULL, start_routine, \
						info->philo[i]) != 0)
				return (free_fun(info), 1);
		}
	}
	return (0);
}

int	init_muthread(t_info *info)
{
	if (malloc_all(info) == 1)
		return (1);
	if (info->nb_philo % 2 == 0)
	{
		if (launch_it(info) == 1)
			return (1);
	}
	else
	{
		if (launch_it_odd(info) == 1)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	int			i;
	t_reaper	reaper;

	i = -1;
	info.reaper = &reaper;
	if (pthread_mutex_init(&info.writing, NULL) != 0)
		return (1);
	if (check_arg(argc, argv, &info) == 1)
		return (1);
	if (init_muthread(&info) == 1)
		return (1);
	while (++i < info.nb_philo)
		pthread_join(*info.thread_philo[i], NULL);
	pthread_join(info.reaper->my_reaper, NULL);
	free_fun(&info);
	return (0);
}
