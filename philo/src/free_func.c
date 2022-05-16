/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:44:36 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/16 16:45:44 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_fun(t_info *info)
{
	int	i;

	i = 0;
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
}
