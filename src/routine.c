/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:30 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/28 19:54:03 by kscordel         ###   ########.fr       */
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

int	timemsg(int num, long lastmeal, int time_to_die, char *str)
{
	long t;

	t = gettime() - lastmeal;
	if (t > (long)time_to_die)
	{
		printf("suce\n");
			return (1);
	}
	printf("%ld %d %s\n", t / 1000, num, str);
	return (0);
}

int	ft_eat(t_philo *info, int num_philo, long *lastmeal)
{
	if (timemsg(num_philo, *lastmeal, info->time_to_die, "is eating"))
		return (1);
	*lastmeal = gettime();
	if (info->nb_of_eat == LLONG_MIN)
		info->nb_of_eat += 1;
	else if (info->nb_of_eat < 0)
		info->nb_of_eat -= 1;
	else if (info->nb_of_eat > 0)
		info->nb_of_eat -= 1;
	ft_usleep(info->time_to_eat);
	return (0);
}

int	paire(t_hand *hand, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_G);
	if (timemsg(hand->num_philo, *lastmeal, hand->info.time_to_die, "has taken a fork"))
		return ((void)pthread_mutex_unlock(hand->fourchette_G), 1);
		
	pthread_mutex_lock(hand->fourchette_D);
	if (timemsg(hand->num_philo, *lastmeal, hand->info.time_to_die, "has taken a fork"))	
		return ((void)pthread_mutex_unlock(hand->fourchette_G), (void)pthread_mutex_unlock(hand->fourchette_D), 1);

	ft_eat(&hand->info, hand->num_philo, lastmeal);
	pthread_mutex_unlock(hand->fourchette_D);
	pthread_mutex_unlock(hand->fourchette_G);
	return (0);
}

int	impaire(t_hand *hand, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_D);
	if (timemsg(hand->num_philo, *lastmeal, hand->info.time_to_die, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_D), 1);
	
	pthread_mutex_lock(hand->fourchette_G);
	if (timemsg(hand->num_philo, *lastmeal, hand->info.time_to_die, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_G), pthread_mutex_unlock(hand->fourchette_D), 1);
		
	
	ft_eat(&hand->info, hand->num_philo, lastmeal);
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
	timemsg(hand->num_philo, lastmeal, hand->info.time_to_die, "is thinking");
	//if (hand->num_philo % 2 == 0)
	//		usleep(hand->info.time_to_eat / 10);
	while (gettime() - lastmeal < hand->info.time_to_die)
	{
		if (hand->num_philo % 2 == 0)
		{
			if (paire(hand, &lastmeal))
				break ;
		}
		else
		{
			if (impaire(hand, &lastmeal))
				break ;
		}
		if (timemsg(hand->num_philo, lastmeal, hand->info.time_to_die, "is sleeping"))
			break ;
		ft_usleep(hand->info.time_to_sleep);
		if (timemsg(hand->num_philo, lastmeal, hand->info.time_to_die, "is thinking"))
			break ;
	}
	timemsg(hand->num_philo, lastmeal, hand->info.time_to_die * 10, "is dead");
	return (NULL);
}