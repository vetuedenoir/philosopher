/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:39 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 18:11:26 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	special(t_hand *hand, t_philo *data)
{
	if (data->num_of_philos % 2 != 0)
	{
		if (data->time_to_eat * 3 <= data->time_to_die && \
			data->time_to_sleep < data->time_to_eat)
			hand->sync += data->time_to_eat - data->time_to_sleep;
		else if (data->time_to_eat * 3 > data->time_to_die && \
			(data->time_to_sleep + data->time_to_eat) < data->time_to_die)
			hand->sync += data->time_to_die - \
			(data->time_to_eat + data->time_to_sleep);
	}
	else
	{
		if (data->time_to_eat * 2 > data->time_to_die && \
			(data->time_to_sleep + data->time_to_eat) < data->time_to_die)
			hand->sync += data->time_to_die - \
			(data->time_to_eat + data->time_to_sleep);
	}
}

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
	philo.time_to_die = (long)ft_atoi(argv[2]) * 1000;
	philo.time_to_eat = (long)ft_atoi(argv[3]) * 1000;
	philo.time_to_sleep = (long)ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo.nb_of_eat = ft_atoi(argv[5]);
	else
		philo.nb_of_eat = -1;
	if (parse(argv, argc) || philo.num_of_philos <= 0 || philo.time_to_die <= 0 \
		|| philo.time_to_eat <= 0 || philo.time_to_sleep <= 0)
		return (printf("wrong arg \n"), \
			philo.num_of_philos = 0, philo);
	return (philo);
}

void	set_all(t_hand *hand, t_philo data, pthread_mutex_t *fourchettes, int i)
{
	hand->fourchette_d = &fourchettes[i];
	hand->info = data;
	hand->num_philo = i + 1;
	hand->is_dead = &fourchettes[data.num_of_philos];
	hand->ecrire = &fourchettes[data.num_of_philos + 1];
	if (data.num_of_philos == 3)
	{
		if (i % 2 == 0)
			hand->sync = 500;
		else
			hand->sync = 1000;
	}
	else if (data.num_of_philos % 2 != 0 && i % 2 == 0)
			hand->sync = 1000;
	else if (data.num_of_philos % 2 == 0)
		hand->sync = 500;
	else
		hand->sync = 0;
	special(hand, &data);
}

t_hand	*create_hand(t_philo data, pthread_mutex_t *fourchettes, char *dead)
{
	t_hand	*hands;
	int		i;
	long	time;

	time = gettime();
	hands = malloc(sizeof(t_hand) * data.num_of_philos);
	if (!hands)
		return (NULL);
	i = -1;
	while (++i < data.num_of_philos)
	{
		if (data.num_of_philos == 1)
			hands[i].fourchette_g = NULL;
		else
		{
			if (i > 0)
				hands[i].fourchette_g = &fourchettes[i - 1];
			else
				hands[i].fourchette_g = &fourchettes[data.num_of_philos - 1];
		}
		hands[i].dead = dead;
		hands[i].t_debut = time;
		set_all(&hands[i], data, fourchettes, i);
	}
	return (hands);
}
