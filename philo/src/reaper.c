/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 17:17:27 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	wipe_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo[i]->is_dead = 1;
		unlock_fork(info->philo[i]);
	}
}

void	*reaper(void *start)
{
	t_reaper	*reaper;
	int			i;

	reaper = (t_reaper *)start;
	i = 0;
	while (1)
	{
		if (get_now(reaper->info) - reaper->info->philo[i]->last_time_eat > \
				(unsigned long long)reaper->info->time_to_die)
		{
			printf("%llu %d has died\n", get_now(reaper->info), \
					reaper->info->philo[i]->nb);
			wipe_all(reaper->info);
			return (reaper);
		}
		i++;
		if (i >= reaper->info->nb_philo)
			i = 0;
	}
	return (reaper);
}
