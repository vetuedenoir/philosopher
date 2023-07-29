/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:30 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/29 20:12:08 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long gettime(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	//printf("\n time sec = %ld et time usec = %ld\n", time.tv_sec, time.tv_usec);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	ft_usleep(int time)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(50);
}

int	ft_isitdead(t_hand *hand, long lastmeal)
{
	long t;

	t = gettime() - lastmeal;
	if (t > (long)hand->info.time_to_die)
	{
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", t / 1000, hand->num_philo, "is dead");
			pthread_mutex_unlock(hand->ecrire);
		}
		pthread_mutex_unlock(hand->is_dead);
		return (1);
	}
	return (0);
}

int	timemsg(t_hand *hand, long lastmeal, char *str)
{
	long t;
	char d;

	d = 0;
	t = gettime() - lastmeal;

	if (t > (long)hand->info.time_to_die)
	{
		
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", t / 1000, hand->num_philo, "is dead");
			pthread_mutex_unlock(hand->ecrire);
		}
		pthread_mutex_unlock(hand->is_dead);
		return (1);
	}
	pthread_mutex_lock(hand->is_dead);
	d = *hand->dead;
	pthread_mutex_unlock(hand->is_dead);
	if (d)
		return (1);
	pthread_mutex_lock(hand->ecrire);
	printf("%ld %d %s\n", t / 1000, hand->num_philo, str);
	pthread_mutex_unlock(hand->ecrire);
	return (0);
}

int	ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	if (timemsg(hand, *lastmeal, "is eating"))
		return (1);
	*lastmeal = gettime();
	if (*nb_of_eat == LLONG_MIN)
		*nb_of_eat =  *nb_of_eat + 1;
	else if (*nb_of_eat < 0)
		*nb_of_eat = *nb_of_eat - 1;
	else if (*nb_of_eat > 0)
		*nb_of_eat = *nb_of_eat - 1;
	ft_usleep(hand->info.time_to_eat);
	return (0);
}

int	paire(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_G);
	
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return ((void)pthread_mutex_unlock(hand->fourchette_G), 1);
		
	pthread_mutex_lock(hand->fourchette_D);
	if (timemsg(hand, *lastmeal, "has taken a fork"))	
		return ((void)pthread_mutex_unlock(hand->fourchette_G), (void)pthread_mutex_unlock(hand->fourchette_D), 1);

	ft_eat(hand, nb_of_eat, lastmeal);
	pthread_mutex_unlock(hand->fourchette_D);
	pthread_mutex_unlock(hand->fourchette_G);
	return (0);
}

int	impaire(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_D);

	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_D), 1);
	
	pthread_mutex_lock(hand->fourchette_G);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_G), pthread_mutex_unlock(hand->fourchette_D), 1);
		
	ft_eat(hand, nb_of_eat, lastmeal);
	pthread_mutex_unlock(hand->fourchette_G);
	pthread_mutex_unlock(hand->fourchette_D);
	return (0);
}

void	*routine_paire(void *arg)
{
	t_hand	*hand;
	long	lastmeal;
	
	hand = (t_hand*)arg;
	lastmeal = gettime();
	timemsg(hand, lastmeal, "is thinking");
	//if (hand->num_philo % 2 == 0)
	//		usleep(hand->info.time_to_eat / 10);
	while (!ft_isitdead(hand, lastmeal))
	{
		if (hand->num_philo % 2 == 0)
		{
			if (paire(hand, &hand->info.nb_of_eat, &lastmeal))
				break ;
		}
		else
		{
			if (impaire(hand, &hand->info.nb_of_eat, &lastmeal))
				break ;
		}
		if (timemsg(hand, lastmeal, "is sleeping"))
			break ;
		ft_usleep(hand->info.time_to_sleep);
		if (timemsg(hand, lastmeal, "is thinking"))
			break ;
		if (hand->num_philo % 2 != 0)
			ft_usleep(500);
		if (!hand->info.nb_of_eat)
			break ;
	}
	return (NULL);
}