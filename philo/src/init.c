/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:39 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 14:22:29 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	parse(char **argv, int ac)
{
	int	x;
	int	i;

	x = 1;
	while (x < ac)
	{
		i = -1;
		while (argv[x][++i])
		{
			if (argv[x][i] < 48 || argv[x][i] > 57)
				return (1);
		}
		x++;
	}
	return (0);
}

t_philo	init(char **argv, int argc)
{
	t_philo	philo;

	if (argc < 5)
		return (philo.num_of_philos = 0, philo);
	if (argv[1])
	philo.num_of_philos = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]) * 1000;
	philo.time_to_eat = ft_atoi(argv[3]) * 1000;
	philo.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo.nb_of_eat = ft_atoi(argv[5]);
	else
		philo.nb_of_eat = -1;
	if (parse(argv, argc) || philo.num_of_philos <= 0 || philo.time_to_die <= 0 || \
		philo.time_to_eat <= 0 || philo.time_to_sleep <= 0)
		return (printf("wrong arg \n"), \
			philo.num_of_philos = 0, philo);
	return (philo);
}