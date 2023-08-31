/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:34:49 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/29 17:28:32 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <fcntl.h> 
#include <semaphore.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct s_philo
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	long	nb_of_eat;	
}		t_philo;

typedef struct	s_hand
{
	sem_t			*died;
	sem_t			*fourchettes;
	sem_t			*write;
	long			t_debut;
	t_philo		info;
	pid_t			*list_pid;
	int			sync;
	int			num_philo;
}		t_hand;

// utils
int	ft_atoi(const char *nptr);
void	ft_usleep(int time);
t_philo	init(char **argv, int argc);
void	kill_all(pid_t *list_pid, int index);

//les routines
void	routine(t_hand hand, int num);

//monitoring.c
void	monitoring(t_philo philo, pid_t *list_pid, t_hand hand);

//dead_no_eat
int	ft_isitdead(t_hand *hand, long lastmeal);
int	timemsg(t_hand *hand, long lastmeal, char *str);
int	ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal);
long	gettime(void);

#endif
