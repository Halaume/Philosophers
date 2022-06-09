/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/09 14:26:08 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	split_odd(t_info *info, int i)
{
	while (i < info->nb_philo)
	{
		if (pthread_create(info->thread_philo[i], NULL, start_routine, \
					info->philo[i]) != 0)
			return (free_fun(info), 1);
		i += 2;
	}
	return (0);
}

int	launch_it_odd(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (i != info->nb_philo - 3)
		{
			if (pthread_create(info->thread_philo[i], NULL, start_routine, \
						info->philo[i]) != 0)
				return (free_fun(info), 1);
		}
		i += 2;
	}
	sleeping(info->time_to_eat / 2 - 10);
	if (pthread_create(info->thread_philo[info->nb_philo - 3], NULL, \
				start_routine, info->philo[info->nb_philo - 3]) != 0)
		return (free_fun(info), 1);
	sleeping(info->time_to_eat / 4);
	if (split_odd(info, 1) == 1)
		return (1);
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
