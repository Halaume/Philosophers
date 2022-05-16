/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/16 16:38:29 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_this_philo(t_info *info, t_philo *philo, int nb)
{
	philo->info = info;
	philo->nb_eat = 0;
	philo->last_time_eat = 0;
	philo->my_nb = nb;
}

void	sleeping(useconds_t time)
{
	while (time > 99999)
	{
		usleep(100000);
		time -= 100000;
	}
	usleep(time);
}

void	*start_routine(void *start)
{
	t_philo	*philo;

	philo = (t_philo *)start;
	return (philo);
}
