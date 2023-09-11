/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:22:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 18:09:49 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"


void	ft_usleep(int time)
{
	long	x;

	x = gettime();
	//printf("gettime > %ld \n ", x);
	while (gettime() - x < time)
		usleep(200);
}

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	//printf("tv_sec : %ld	tv_usec : %ld \n", time.tv_sec * 1000, time.tv_usec / 1000);
	return ((time.tv_sec * 1000000) + ((time.tv_usec / 1000) * 1000));
}

void	usleep_precision(int time)
{
	long	x;

	x = gettime();
	//printf("gettime > %ld \n ", x);
	while (gettime() - x < time)
		usleep(200);
}

long	gettime_precision(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	//printf("tv_sec : %ld	tv_usec : %ld \n", time.tv_sec * 1000, time.tv_usec / 1000);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	depart(t_hand hand)
{
	if (hand.info.num_of_philos % 2 == 0 && hand.info.num_of_philos > 100 && \
		hand.info.num_of_philos < 150)
	{
		while (gettime() < hand.t_debut + 2000)
		usleep(200);
	}
	else if (hand.info.num_of_philos % 2 == 0 && hand.info.num_of_philos > 150)
	{
		while (gettime() < hand.t_debut + 3600)
		usleep(200);
	}

	if (hand.info.num_of_philos % 2 == 0 && hand.num_philo % 2 != 0)
		ft_usleep(hand.info.time_to_eat / 2);
	else if (hand.info.num_of_philos % 2 != 0 && hand.num_philo % 2 == 0 )
		ft_usleep(hand.info.time_to_eat / 2);
	
}
