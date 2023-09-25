/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:51:46 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/25 13:48:24 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int		num_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_of_eat;	
}		t_philo;

typedef struct s_hand
{
	pthread_mutex_t	*fourchette_g;
	pthread_mutex_t	*fourchette_d;
	pthread_mutex_t	*is_dead;
	pthread_mutex_t	*ecrire;
	char			*dead;
	long			t_debut;
	t_philo			info;
	int				sync;
	int				num_philo;
}		t_hand;

//	init.c
t_philo	init(char **argv, int argc);
void	set_all(t_hand *hand, t_philo data, pthread_mutex_t *fourchettes, \
	int i);
t_hand	*create_hand(t_philo data, pthread_mutex_t *fourchettes, char *dead);

//	routine.c
void	*routine(void *arg);

//	dead_no_eat.c
int		ft_isitdead(t_hand *hand, long lastmeal);
int		timemsg(t_hand *hand, long lastmeal, char *str);

//	action.c
int		ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal);
int		ft_sleep(t_hand *hand, long lastmeal);

//	time.c
long	gettime_precision(void);
void	usleep_precision(int time);
long	gettime(void);
int		ft_usleep(t_hand *hand, long lastmeal, int time);
void	depart(t_hand *hand, long *lastmeal);

//	utils.c
int		ft_atoi(const char *nptr);
void	clear_mutex(pthread_mutex_t *fourchettes, int indice);
int		mutex_init(t_philo data, pthread_mutex_t *fourchettes);

#endif
