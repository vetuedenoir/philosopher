/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:18:45 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/29 17:32:13 by kscordel         ###   ########.fr       */
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
	return (nbr * signe);
}

void	clear_mutex(pthread_mutex_t *fourchettes, int indice)
{
	int	i;

	i = 0;
	while (i < indice)
	{
		pthread_mutex_destroy(&fourchettes[i]);
		i++;
	}
}

int	mutex_init(t_philo data, pthread_mutex_t *fourchettes)
{
	int	i;

	i = 0;
	while (i < data.number_of_philosophers + 2)
	{
		if (pthread_mutex_init(&fourchettes[i], NULL) == -1)
			return (clear_mutex(fourchettes, i), 1);
		i++;
	}
	return (0);
}

long gettime(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	//printf("\n time sec = %ld et time usec = %ld\n", time.tv_sec, time.tv_usec);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	ft_usleep(int time)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(50);
}