/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:30 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/24 17:57:44 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*paire(void *arg)
{
	t_hand	*hand;

	hand = (t_hand*)arg;
	printf("salut c est philo numero %d \n", hand->num_philo);
	while (1)
	{
		pthread_mutex_lock(hand->fourchette_D);
		printf("philo %d has taken a fork\n", hand->num_philo);
		pthread_mutex_lock(hand->fourchette_G);
		printf("philo %d his eating\n", hand->num_philo);
		*(hand->fourch_D) = 1;
		*(hand->fourch_G) = 1;
		usleep(hand->info.time_to_eat);
		pthread_mutex_unlock(hand->fourchette_D);
		pthread_mutex_unlock(hand->fourchette_G);
		printf("philo %d his sleeping\n", hand->num_philo);
		usleep(hand->info.time_to_sleep);
		printf("philo %d his thinking\n", hand->num_philo);
	}
}