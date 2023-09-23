/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:31:40 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 16:05:35 by kscordel         ###   ########.fr       */
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
	ft_usleep(hand, *lastmeal, hand->info.time_to_eat);
	return (0);
}

int	ft_sleep(t_hand *hand, long lastmeal)
{
	if (timemsg(hand, lastmeal, "is sleeping"))
		return (1);
	if (ft_usleep(hand, lastmeal, hand->info.time_to_sleep))
		return (0);
	return (0);
}

void	byby(t_hand *hand)
{
	usleep(hand->info.time_to_eat);
	usleep(hand->info.time_to_sleep);
	usleep(500000);
	sem_post(hand->died);
	usleep(100000);
	exit(0);
}
