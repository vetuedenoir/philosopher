/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:51:46 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 16:05:01 by kscordel         ###   ########.fr       */
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
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
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

// utils
int		ft_atoi(const char *nptr);
void	clear_mutex(pthread_mutex_t *fourchettes, int indice);
int		mutex_init(t_philo data, pthread_mutex_t *fourchettes);
void	ft_usleep(int time);
t_philo	init(char **argv, int argc);

//les routines
void	*routine(void *arg);

//dead_no_eat
int		ft_isitdead(t_hand *hand, long lastmeal);
int		timemsg(t_hand *hand, long lastmeal, char *str);
int		ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal);
long	gettime(void);

//time
long	gettime_precision(void);
void	usleep_precision(int time);
void    depart(t_hand hand);

int	ft_sleep(t_hand *hand, long lastmeal);

#endif
