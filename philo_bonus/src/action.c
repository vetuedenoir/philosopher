/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:31:40 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/12 16:35:33 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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

int	ft_sleep(t_hand *hand, long lastmeal)
{
	long	x;
	long	d;
	long	t;

	t = gettime();
	d = lastmeal + hand->info.time_to_die;
	if (timemsg(hand, lastmeal, "is sleeping"))
		return (1);
	x = gettime() + hand->info.time_to_sleep;
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
