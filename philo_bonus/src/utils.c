/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:25:01 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 17:06:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		signe;
	long	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	if (nbr > 2147483647)
		return (0);
	return (nbr * signe);
}

int	timemsg(t_hand *hand, long lastmeal, char *str)
{
	if (ft_isitdead(hand, lastmeal))
		return (1);
	sem_wait(hand->alive);
	sem_wait(hand->write);
	printf("%ld %d %s\n", (gettime() - hand->t_debut) \
		/ 1000, hand->num_philo, str);
	sem_post(hand->write);
	sem_post(hand->alive);
	return (0);
}

int	ft_isitdead(t_hand *hand, long lastmeal)
{
	long	t;

	t = gettime() - lastmeal;
	if (t > (long)hand->info.time_to_die)
	{
		sem_wait(hand->alive);
		sem_wait(hand->write);
		printf("%ld %d %s\n", (gettime() - hand->t_debut) \
			/ 1000, hand->num_philo, "is died");
		sem_post(hand->died);
		sem_post(hand->write);
		exit(0);
	}
	return (0);
}
