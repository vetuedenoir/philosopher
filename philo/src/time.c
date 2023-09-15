/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:22:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/15 19:37:01 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

/*void	ft_usleep(int time, t_hand hand)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(200);
}*/

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

void	depart(t_hand hand, long lastmeal)
{
	if (hand.info.num_of_philos % 2 == 0 && hand.info.num_of_philos > 100 && \
		hand.info.num_of_philos < 150)
	{
		while (gettime() < hand.t_debut + 2000)
			usleep(500);
	}
	else if (hand.info.num_of_philos % 2 == 0 && hand.info.num_of_philos > 150)
	{
		while (gettime() < hand.t_debut + 3500)
			usleep(500);
	}
	if (hand.info.num_of_philos % 2 == 0 && hand.num_philo % 2 != 0)
		ft_usleep(&hand, lastmeal, hand.info.time_to_eat / 2);
	else if (hand.info.num_of_philos % 2 != 0 && hand.num_philo % 2 == 0)
		ft_usleep(&hand, lastmeal, hand.info.time_to_eat / 2);
}
