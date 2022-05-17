/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:07:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 12:09:45 by ghanquer         ###   ########.fr       */
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
	if (info->nb_philo < 1 || info->time_to_die < 0 || info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (1);
	if (info->nb_philo == 1)
		return (do_one(info), 1);
	if (info->time_to_die == 0)
		return (die_zero(), 1);
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
		info->nb_of_eat = ft_atoi(argv[6]);
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
	info->philo = NULL;
	info->thread_philo = NULL;
	info->fork = NULL;
	return (0);
}

int	init_muthread(t_info *info)
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
		if (!info->fork[i])
			return (free_fun(info), 1);
		if (pthread_mutex_init(info->fork[i], NULL) != 0)
			return (free_fun(info), 1);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		info->thread_philo[i] = malloc(sizeof(pthread_t) * 1);
		info->philo[i] = malloc(sizeof(t_philo) * 1);
		if (!info->thread_philo || !info->philo)
			return (free_fun(info), 1);
		init_this_philo(info, info->philo[i], i + 1);
		if (pthread_create(info->thread_philo[i], NULL, start_routine, info->philo[i]) != 0)
			return (free_fun(info), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	i = 0;
	if (check_arg(argc, argv, &info) == 1)
		return (1);
	if (init_muthread(&info) == 1)
		return (1);
	while (i < info.nb_philo)
		pthread_join(*info.thread_philo[i], NULL);
	return (0);
}
