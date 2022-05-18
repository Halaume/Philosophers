/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:20:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/18 11:59:23 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	do_one(t_info *info)
{
	printf("0 1 has taken a fork\n");
	sleeping(info->time_to_die);
	printf("%d 1 died\n", info->time_to_die);
}

void	die_zero(void)
{
	printf("0 1 died\n");
}

int	double_check(t_info *info)
{
	if (info->nb_philo < 1 || info->time_to_die < 0 || info->time_to_eat < 0 \
			|| info->time_to_sleep < 0)
		return (1);
	if (info->nb_philo == 1)
		return (do_one(info), 1);
	if (info->time_to_die == 0)
		return (die_zero(), 1);
	info->philo = NULL;
	info->thread_philo = NULL;
	info->fork = NULL;
	info->fork_lock = NULL;
	return (0);
}

int	check_arg(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (argc == 6)
	{
		info->nb_of_eat = ft_atoi(argv[5]);
		if (info->nb_of_eat < 0)
			return (1);
	}
	else
		info->nb_of_eat = -1;
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&info->get_time, NULL);
	info->start_time = info->get_time;
	if (double_check(info) == 1)
		return (1);
	return (0);
}