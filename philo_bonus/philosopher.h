/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:48 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 18:07:31 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h> 
# include <semaphore.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	sem_t			*alive;
	sem_t			*died;
	sem_t			*fourchettes;
	sem_t			*write;
	long			t_debut;
	t_philo			info;
	pid_t			*list_pid;
	int				sync;
	int				num_philo;
}		t_hand;

//	init.c
t_philo	init(char **argv, int argc);
t_hand	creat_hand(t_philo philo);

//	action.c
int		ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal);
int		ft_sleep(t_hand *hand, long lastmeal);
void	byby(t_hand *hand);

//	routine.c
void	routine(t_hand hand, int num);

//monitoring.c
void	monitoring(t_philo philo, pid_t *list_pid, t_hand hand);
void	kill_all(pid_t *list_pid, int index);

//	utils.c
int		ft_isitdead(t_hand *hand, long lastmeal);
int		timemsg(t_hand *hand, long lastmeal, char *str);
int		ft_atoi(const char *nptr);

//	time.c
int		ft_usleep(t_hand *hand, long lastmeal, int time);
long	gettime(void);
void	usleep_precision(int time);
long	gettime_precision(void);
void	depart(t_hand hand);

#endif
