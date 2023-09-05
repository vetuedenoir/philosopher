/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:32:48 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/05 11:36:44 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	byby(t_hand *hand)
{
	write(1, "byby\n", 5);
	ft_usleep(hand->info.time_to_eat);
	ft_usleep(hand->info.time_to_sleep);
	ft_usleep(500000);
	sem_post(hand->died);
	ft_usleep(100000);
	exit(0);
}

void	lonely(t_hand *hand, long lastmeal)
{
	sem_wait(hand->fourchettes);
	if (timemsg(hand, lastmeal, "has taken a fork"))
	{
		sem_post(hand->fourchettes);
		exit(0);
	}
	ft_usleep(hand->info.time_to_die);
	ft_isitdead(hand, lastmeal);
	exit(0);
}

int	ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	if (timemsg(hand, *lastmeal, "is eating"))
		return (1);
	*lastmeal = gettime();
	if (*nb_of_eat > 0)
		*nb_of_eat = *nb_of_eat - 1;
	ft_usleep(hand->info.time_to_eat);
	return (0);
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

	lastmeal = gettime();
	hand.num_philo = num;
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
		ft_usleep(hand.info.time_to_sleep);
		if (timemsg(&hand, lastmeal, "is thinking"))
			exit(0);
		if (hand.info.num_of_philos % 2 != 0)
			ft_usleep(500);
	}
	exit(0);
}
