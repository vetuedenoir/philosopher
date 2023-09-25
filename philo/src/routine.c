/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:30 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/25 13:48:12 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*lonely(t_hand *hand, long lastmeal)
{
	pthread_mutex_lock(hand->fourchette_d);
	if (timemsg(hand, lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_d), NULL);
	usleep(hand->info.time_to_die + 500);
	ft_isitdead(hand, lastmeal);
	pthread_mutex_unlock(hand->fourchette_d);
	return (NULL);
}

int	paire(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_g);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_g), 1);
	pthread_mutex_lock(hand->fourchette_d);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_g), \
			pthread_mutex_unlock(hand->fourchette_d), 1);
	ft_eat(hand, nb_of_eat, lastmeal);
	pthread_mutex_unlock(hand->fourchette_d);
	pthread_mutex_unlock(hand->fourchette_g);
	return (0);
}

int	impaire(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	pthread_mutex_lock(hand->fourchette_d);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_d), 1);
	pthread_mutex_lock(hand->fourchette_g);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
		return (pthread_mutex_unlock(hand->fourchette_g), \
			pthread_mutex_unlock(hand->fourchette_d), 1);
	ft_eat(hand, nb_of_eat, lastmeal);
	pthread_mutex_unlock(hand->fourchette_g);
	pthread_mutex_unlock(hand->fourchette_d);
	return (0);
}

int	for_all(t_hand *hand, long lastmeal)
{
	if (!hand->info.nb_of_eat)
		return (1);
	if (ft_sleep(hand, lastmeal))
		return (1);
	if (timemsg(hand, lastmeal, "is thinking"))
		return (1);
	usleep_precision(hand->sync);
	return (0);
}

void	*routine(void *arg)
{
	t_hand	*hand;
	long	lastmeal;

	hand = (t_hand *)arg;
	lastmeal = 0;
	depart(hand, &lastmeal);
	if (hand->info.num_of_philos == 1)
		return (lonely(hand, lastmeal));
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
		if (for_all(hand, lastmeal))
			break ;
	}
	return (NULL);
}
