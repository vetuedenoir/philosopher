/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:22:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/25 15:04:51 by kscordel         ###   ########.fr       */
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
		usleep(330);
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

void	depart(t_hand *hand, long *lastmeal)
{
	hand->t_debut = hand->t_debut + (hand->info.num_of_philos * 1000);
	while (gettime() < hand->t_debut)
		usleep(1000);
	*lastmeal = gettime();
	timemsg(hand, *lastmeal, "is thinking");
	if (hand->info.num_of_philos % 2 == 0 && hand->num_philo % 2 != 0)
		usleep(hand->info.time_to_eat / 2);
	else if (hand->info.num_of_philos % 2 != 0 && hand->num_philo % 2 == 0)
		usleep(hand->info.time_to_eat / 2);
}
