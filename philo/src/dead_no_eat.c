/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_no_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:32:00 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 18:04:36 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_isitdead(t_hand *hand, long lastmeal)
{
	long	t;

	t = gettime() - lastmeal;
	if (t > (long)hand->info.time_to_die)
	{
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", (gettime() - hand->t_debut) \
				/ 1000, hand->num_philo, "is died");
			pthread_mutex_unlock(hand->ecrire);
				
		}
		pthread_mutex_unlock(hand->is_dead);
		return (1);
	}
	return (0);
}

int	timemsg(t_hand *hand, long lastmeal, char *str)
{
	char	d;

	d = 0;
	if (gettime() - lastmeal > (long)hand->info.time_to_die)
	{
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", (gettime() - hand->t_debut) \
				/ 1000, hand->num_philo, "died");
			pthread_mutex_unlock(hand->ecrire);
		}
		return (pthread_mutex_unlock(hand->is_dead), 1);
	}
	pthread_mutex_lock(hand->is_dead);
	d = *hand->dead;
	pthread_mutex_unlock(hand->is_dead);
	if (d)
		return (1);
	pthread_mutex_lock(hand->ecrire);
	printf("%ld %d %s\n", (gettime() - hand->t_debut) \
		/ 1000, hand->num_philo, str);
	return (pthread_mutex_unlock(hand->ecrire), 0);
}
