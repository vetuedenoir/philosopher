/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:30:15 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 18:08:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_usleep(t_hand *hand, long lastmeal, int time)
{
	long	x;
	long	d;
	long	t;

	t = gettime();
	d = lastmeal + hand->info.time_to_die;
	x = gettime() + time;
	while (t < x)
	{
		usleep(332);
		t = gettime();
		if (t > d)
		{
			if (ft_isitdead(hand, lastmeal))
				return (1);
		}
	}
	return (0);
}

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + ((time.tv_usec / 1000) * 1000));
}

void	usleep_precision(int time)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(200);
}

long	gettime_precision(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	depart(t_hand hand)
{
	if (hand.info.num_of_philos % 2 == 0 && hand.num_philo % 2 != 0)
		usleep_precision(hand.info.time_to_eat / 2);
	else if (hand.info.num_of_philos % 2 != 0 && hand.num_philo % 2 == 0)
		usleep_precision(hand.info.time_to_eat / 2);
}
