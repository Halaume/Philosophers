/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:00:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/16 16:41:17 by ghanquer         ###   ########.fr       */
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
	int		my_nb;
}	t_philo;

long long	ft_atoi(const char *nptr);
void		free_fun(t_info *info);
void		*start_routine(void *mon_thread);
void		init_this_philo(t_info *info, t_philo *philo, int nb);
void		sleeping(useconds_t time);

#endif
