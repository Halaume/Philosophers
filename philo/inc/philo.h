/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:00:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/19 17:37:16 by ghanquer         ###   ########.fr       */
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
	int				*fork_lock;
	struct s_philo	**philo;
	struct s_reaper	*reaper;
	struct timeval	get_time;
	struct timeval	start_time;
	int				nb_of_eat;
	int				is_dead;
	pthread_t		**thread_philo;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	writing;
	pthread_mutex_t	**fork;
}	t_info;

typedef struct s_philo
{
	struct timeval	start;
	struct timeval	get_time;
	int				nb_eat;
	int				nb_of_eat;
	int				last_time_eat;
	int				nb;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				**fork_lock;
	int				*is_dead;
	struct s_reaper	**reaper;
	pthread_mutex_t	*writing;
	pthread_mutex_t	***fork;
}	t_philo;

typedef struct s_reaper
{
	t_info			*info;
	pthread_t		my_reaper;
	pthread_mutex_t	scythe;
}	t_reaper;

//						INIT

int					check_arg(int argc, char **argv, t_info *info);
void				init_this_philo(t_info *info, t_philo *philo, int nb);

//						ROUTINE

void				*start_routine(void *mon_thread);
void				sleeping(useconds_t time);
void				is_sleeping(t_philo *philo);
void				take_fork(t_philo *philo);

//						REAPER

void				*reaper(void *start);
void				wipe_all(t_info *info);
void				set_last_eat(t_philo *philo, t_reaper *reaper);
unsigned long long	get_last_eat(t_philo *philo, t_reaper *reaper);

//						PRINT

void				ft_putnbr(unsigned long long nb);
int					ft_putstr(char *str, t_philo *philo);

//						FREE

void				free_fun(t_info *info);
void				destroy_mut(t_info *info);

//						UTILS

long long			ft_atoi(const char *nptr);
unsigned long long	get_now(t_philo *philo);
int					is_dead(t_philo *philo, t_reaper *reaper);
void				sleeping(useconds_t time);
void				unlock_fork(t_philo *philo);
int					have_all_eat(t_info *info, t_reaper *reaper);

#endif
