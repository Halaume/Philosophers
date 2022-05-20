/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:51:00 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/20 16:52:34 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_this_philo(t_info *info, t_philo *philo, int nb)
{
	philo->nb_eat = 0;
	philo->last_time_eat = 0;
	philo->nb = nb;
	philo->start = info->start_time;
	philo->is_dead = &info->is_dead;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->fork_lock = &info->fork_lock;
	philo->reaper = &info->reaper;
	philo->nb_philo = info->nb_philo;
	philo->fork = &info->fork;
	philo->nb_of_eat = info->nb_of_eat;
	philo->writing = &info->writing;
}

unsigned long long	get_now(t_philo *philo)
{
	unsigned long long	now;

	gettimeofday(&philo->get_time, NULL);
	now = ((philo->get_time.tv_sec - 1 - philo->start.tv_sec) * 1000000) + \
			1000000 + (philo->get_time.tv_usec - philo->start.tv_usec);
	now = now / 1000;
	return (now);
}

void	sleeping(useconds_t time)
{
	time = time * 1000;
	while (time > 99999)
	{
		usleep(100000);
		time -= 100000;
	}
	usleep(time);
}

void	is_sleeping(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
		return ;
	ft_putstr("is sleeping\n", philo);
	sleeping(philo->time_to_sleep);
	if (is_dead(philo, *philo->reaper) == 1)
		return ;
	ft_putstr("is thinking\n", philo);
}

void	eating(t_philo *philo)
{
	if (is_dead(philo, *philo->reaper) == 1)
	{
		unlock_fork(philo);
		return ;
	}
	ft_putstr("is eating\n", philo);
	set_last_eat(philo, *philo->reaper);
	sleeping(philo->time_to_eat);
	unlock_fork(philo);
	is_sleeping(philo);
}
