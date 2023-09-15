/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:21:07 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/15 19:43:00 by kscordel         ###   ########.fr       */
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
	if (ft_usleep(hand, *lastmeal, hand->info.time_to_eat))
		return (0);
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
