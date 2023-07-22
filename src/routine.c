/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:30 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/21 18:43:46 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long gettime(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	//printf("\n time sec = %ld et time usec = %ld\n", time.tv_sec, time.tv_usec);
	return ((time.tv_sec * 1000) + time.tv_usec);
}

void	*paire(void *arg)
{
	t_hand	*hand;
	long	diff;
	long	t;
	
	hand = (t_hand*)arg;
	diff = gettime();;
	printf("salut c est philo numero %d \n", hand->num_philo);
	while (1)
	{
		pthread_mutex_lock(hand->fourchette_D);
		printf("philo %d has taken a fork\n", hand->num_philo);
		pthread_mutex_lock(hand->fourchette_G);
		t = gettime() - diff; 
		if (t > hand->info.time_to_die)
		{
			printf("philo %d is DEAD %ld\n", hand->num_philo, t);
			return (NULL);
		}
		
		printf("philo %d his eating\n", hand->num_philo);
		printf("t eat de philo %d = %ld\n\n", hand->num_philo, t);
		*(hand->fourch_D) = hand->num_philo;
		*(hand->fourch_G) = hand->num_philo;
		diff = gettime();
		usleep(hand->info.time_to_eat);
		pthread_mutex_unlock(hand->fourchette_D);
		pthread_mutex_unlock(hand->fourchette_G);
		
		printf("philo %d his sleeping\n", hand->num_philo);
		printf("t sleep de philo %d = %ld real time = %ld\n\n", hand->num_philo, gettime() - diff, gettime());
		usleep(hand->info.time_to_sleep);
		
		printf("philo %d his thinking\n", hand->num_philo);
		printf("t thi de philo %d = %ld\n\n", hand->num_philo, gettime() - diff);
	}
	printf("DEAD\n");
}