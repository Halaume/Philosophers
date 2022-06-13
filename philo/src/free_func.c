/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:44:36 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/10 15:41:25 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_info_is_init(t_info *info)
{
	int	i;

	i = -1;
	info->is_init = NULL;
	info->is_init = malloc(sizeof(int) * info->nb_philo);
	if (!info->is_init)
		return (1);
	while (++i < info->nb_philo)
		info->is_init[i] = 0;
	return (0);
}

void	destroy_mut(t_info *info)
{
	int	i;

	i = 0;
	if (info->reaper->scythe_done == 1)
		pthread_mutex_destroy(&info->reaper->scythe);
	if (info->is_init)
	{
		while (i < info->nb_philo)
		{
			if (info->is_init[i] == 1)
				pthread_mutex_destroy(info->fork[i]);
			i++;
		}
	}
	if (info->writing_done == 1)
		pthread_mutex_destroy(&info->writing);
}

void	free_fun(t_info *info)
{
	int	i;

	i = 0;
	destroy_mut(info);
	while (i < info->nb_philo)
	{
		if (info->thread_philo[i])
			free(info->thread_philo[i]);
		if (info->fork[i])
			free(info->fork[i]);
		if (info->philo[i])
			free(info->philo[i]);
		i++;
	}
	if (info->fork)
		free(info->fork);
	if (info->philo)
		free(info->philo);
	if (info->thread_philo)
		free(info->thread_philo);
	if (info->is_init)
		free(info->is_init);
}
