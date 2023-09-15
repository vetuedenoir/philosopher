/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:30:15 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/14 17:00:12 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	ft_usleep(int time)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(200);
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
		ft_usleep(hand.info.time_to_eat / 2);
	else if (hand.info.num_of_philos % 2 != 0 && hand.num_philo % 2 == 0)
		ft_usleep(hand.info.time_to_eat / 2);
}
