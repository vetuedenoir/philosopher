/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:21:07 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 17:35:50 by kscordel         ###   ########.fr       */
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
	char	i;

	i = 0;
	x = gettime();
	(void) lastmeal;
	while (gettime() - x < hand->info.time_to_sleep)
	{
		usleep(200);
		if (i == 10)
		{
			if (ft_isitdead(hand, lastmeal))
			return (1);
			i = 0;
		}
		i++;
	}
	return (0);
}