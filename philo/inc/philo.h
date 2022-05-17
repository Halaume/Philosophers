/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:00:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/17 14:45:40 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	struct s_philo	**philo;
	struct timeval	get_time;
	struct timeval	start_time;
	int				nb_of_eat;
	pthread_t		**thread_philo;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	**fork;
}	t_info;

typedef struct s_philo
{
	t_info	*info;
	int		nb_eat;
	int		last_time_eat;
	int		is_dead;
	int		nb;
}	t_philo;

typedef struct s_reaper
{
	t_info		*info;
	pthread_t	my_reaper;
}	t_reaper;

long long	ft_atoi(const char *nptr);
void		free_fun(t_info *info);
void		*start_routine(void *mon_thread);
void		*reaper(void *start);
void		init_this_philo(t_info *info, t_philo *philo, int nb);
void		sleeping(useconds_t time);
void		is_sleeping(t_philo *philo);
void		take_fork(t_philo *philo);

#endif
