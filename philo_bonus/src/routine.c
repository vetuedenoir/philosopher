/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:32:48 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/14 16:56:19 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	lonely(t_hand *hand, long lastmeal)
{
	sem_wait(hand->fourchettes);
	if (timemsg(hand, lastmeal, "has taken a fork"))
	{
		sem_post(hand->fourchettes);
		exit(0);
	}
	ft_usleep(hand->info.time_to_die + 500);
	ft_isitdead(hand, lastmeal);
	exit(0);
}

void	take_eat(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	sem_wait(hand->fourchettes);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
	{
		sem_post(hand->fourchettes);
		exit(0);
	}
	sem_wait(hand->fourchettes);
	if (timemsg(hand, *lastmeal, "has taken a fork"))
	{
		sem_post(hand->fourchettes);
		exit(0);
	}
	if (ft_eat(hand, nb_of_eat, lastmeal))
	{
		sem_post(hand->fourchettes);
		sem_post(hand->fourchettes);
		exit(0);
	}
	sem_post(hand->fourchettes);
	sem_post(hand->fourchettes);
}

void	routine(t_hand hand, int num)
{
	long	lastmeal;

	hand.num_philo = num;
	lastmeal = gettime();
	depart(hand);
	timemsg(&hand, lastmeal, "is thinking");
	if (hand.info.num_of_philos == 1)
		lonely(&hand, lastmeal);
	if (num > hand.info.num_of_philos / 2)
		ft_usleep(2000);
	while (1)
	{
		take_eat(&hand, &hand.info.nb_of_eat, &lastmeal);
		if (hand.info.nb_of_eat == 0)
			byby(&hand);
		if (timemsg(&hand, lastmeal, "is sleeping"))
			exit(0);
		if (ft_sleep(&hand, lastmeal))
			exit(0);
		if (timemsg(&hand, lastmeal, "is thinking"))
			exit(0);
		if (hand.info.num_of_philos % 2 != 0)
			usleep_precision(500);
	}
	exit(0);
}
