/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:32:59 by kscordel          #+#    #+#             */
/*   Updated: 2023/07/29 20:10:12 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

t_philo	init(char **argv, int argc)
{
	t_philo	philo;
	
	philo.number_of_philosophers = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]) * 1000;
	philo.time_to_eat = ft_atoi(argv[3]) * 1000;
	philo.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo.nb_of_eat = ft_atoi(argv[5]);
	else
		philo.nb_of_eat = -1;
	return (philo);
}

t_hand	*create_hand(t_philo data, pthread_mutex_t *fourchettes, char *dead)
{
	t_hand	*hands;
	int		i;

	hands = malloc(sizeof(t_hand) * data.number_of_philosophers);
	if (!hands)
		return (NULL);
	i = -1;
	*dead = 0;
	while (++i < data.number_of_philosophers)
	{
		if (data.number_of_philosophers == 1)
			hands[i].fourchette_G = NULL;
		else
		{
			if (i > 0)
				hands[i].fourchette_G = &fourchettes[i - 1];
			else
				hands[i].fourchette_G = &fourchettes[data.number_of_philosophers - 1];
		}
		hands[i].fourchette_D = &fourchettes[i];
		hands[i].info = data;
		hands[i].num_philo = i + 1;
		hands[i].dead = dead;
		hands[i].is_dead = &fourchettes[data.number_of_philosophers];
		hands[i].ecrire = &fourchettes[data.number_of_philosophers + 1];
	}
	return (hands);
}

void	launch(pthread_t *philosophers, t_hand *hands, t_philo data)
{
	int	i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		hands[i].t_debut = gettime();
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			write(2, "erreur : pthread_creat\n", 23);
			return ;
		}
		i += 2;
		hands[i - 1].t_debut = gettime();
	}
	i = 1;
	usleep(data.time_to_eat - 200);
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			write(2, "erreur : pthread_creat\n", 23);
			return ;
		}
		i += 2;
	}
}

int	end(pthread_t *philosophers, t_hand *hands, t_philo data, pthread_mutex_t *f)
{
	int	i;
	int	r;
	
	i = 0;
	r = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_join(philosophers[i], NULL) != 0)
		{
			write(2, "erreur : pthread_join\n", 22);
			r = 1;
		}
		i++;
	}
	clear_mutex(f, data.number_of_philosophers + 2);
	free(philosophers);
	free(f);
	free(hands);
	return (r);
}

int	main(int argc, char *argv[])
{
	t_philo 		philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*fourchettes;
	t_hand			*hands;
	char			dead;

	if (argc < 5)
		return (0);
	philo = init(argv, argc);
	if (philo.number_of_philosophers <= 0 || philo.time_to_die <= 0 || 
		philo.time_to_eat <= 0 || philo.time_to_sleep <= 0)
		return (printf("wrong arg \n"), 0);
	philosophers = malloc(sizeof(pthread_t) * philo.number_of_philosophers);
	if (!philosophers)
		return (1);
	fourchettes = malloc(sizeof(pthread_mutex_t) * (philo.number_of_philosophers + 2));
	if (!fourchettes)
		return (free(philosophers), 1);
	hands = create_hand(philo, fourchettes, &dead);
	if (!hands)
		return (free(philosophers), free(fourchettes), 1);
	if (mutex_init(philo, fourchettes))
		return (free(philosophers), free(fourchettes), free(hands), 1);
	launch(philosophers, hands, philo);
	return (end(philosophers, hands, philo, fourchettes));
}
