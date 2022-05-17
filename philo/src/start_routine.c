/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 17:44:03 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eating(t_philo *philo)
{
	if (is_dead(philo->info) == 1)
		return ;
	printf("%llu %d is eating\n", get_now(philo->info), philo->nb);
	philo->nb_eat++;
	philo->last_time_eat = get_now(philo->info);
	if (have_all_eat(philo->info) == 0)
		wipe_all(philo->info);
	sleeping(philo->info->time_to_eat);
	unlock_fork(philo);
	is_sleeping(philo);
}

int	took_fork(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
		if (is_dead(philo->info) == 1)
			return (1);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		pthread_mutex_lock(philo->info->fork[philo->nb]);
		if (is_dead(philo->info) == 1)
			return (1);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
	}
	else
	{
		pthread_mutex_lock(philo->info->fork[philo->nb]);
		if (is_dead(philo->info) == 1)
			return (1);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
		if (is_dead(philo->info) == 1)
			return (1);
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
	}
	return (0);
}

void	take_fork(t_philo *philo)
{
	if (is_dead(philo->info) == 1)
		return ;
	if (philo->nb != philo->info->nb_philo)
	{
		if (took_fork(philo) == 1)
			return ;
	}
	else
	{
		pthread_mutex_lock(philo->info->fork[0]);
		if (is_dead(philo->info) == 1)
			return ;
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
		pthread_mutex_lock(philo->info->fork[philo->nb - 1]);
		if (is_dead(philo->info) == 1)
			return ;
		printf("%llu %d has taken a fork\n", get_now(philo->info), philo->nb);
	}
	eating(philo);
}

void	*start_routine(void *start)
{
	t_philo	*philo;

	philo = (t_philo *)start;
	while (1)
	{
		if (is_dead(philo->info) == 1)
			break ;
		take_fork(philo);
	}
	return (philo);
}
