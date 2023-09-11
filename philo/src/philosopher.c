/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:32:59 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/11 17:58:46 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
	else if (data.num_of_philos % 2 != 0 && i % 2 != 0)
			hand->sync = 1000;
	else if (data.num_of_philos % 2 == 0)
		hand->sync = 0;
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

int	end(pthread_t *philosophers, t_hand *hands, t_philo data, \
	pthread_mutex_t *f)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (i < data.num_of_philos)
	{
		if (pthread_join(philosophers[i], NULL) != 0)
		{
			write(2, "erreur : pthread_join\n", 22);
			r = 1;
		}
		i++;
	}
	clear_mutex(f, data.num_of_philos + 2);
	free(philosophers);
	free(f);
	free(hands);
	return (r);
}

int	launch(pthread_t *philosophers, t_hand *hands, t_philo data, pthread_mutex_t *f)
{
	int	i;

	i = 0;
	while (i < data.num_of_philos)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			//write(2, "erreur : pthread_creat\n", 23);
			while (--i >= 0)
			{
				if (pthread_join(philosophers[i], NULL) != 0)
					write(2, "erreur : pthread_join\n", 22);
				
			}
			
			//return(end(philosophers, hands, data, f));
			return (free(philosophers), free(hands), clear_mutex(f, data.num_of_philos + 2), free(f), 1);
		}
		i += 1;
	}
	return (0);
	
/*
	(void)f;
	while (i < data.num_of_philos)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			write(2, "erreur : pthread_creat\n", 23);
			return (free(philosophers), free(hands), 1);
		}
		i += 2;
	}
	i = 1;
	usleep(data.time_to_eat / 4);
	while (i < data.num_of_philos)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			write(2, "erreur : pthread_creat\n", 23);
			return (free(philosophers), free(hands), 1);
		}
		i += 2;
	}
	return (0);*/
}

int	main(int argc, char *argv[])
{
	t_philo			philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*fourchettes;
	t_hand			*hands;
	char			dead;

	philo = init(argv, argc);
	if (!philo.num_of_philos)
		return (1);
	philosophers = malloc(sizeof(pthread_t) * philo.num_of_philos);
	if (!philosophers)
		return (1);
	fourchettes = malloc(sizeof(pthread_mutex_t) * \
		(philo.num_of_philos + 2));
	if (!fourchettes)
		return (free(philosophers), 1);
	dead = 0;
	hands = create_hand(philo, fourchettes, &dead);
	if (!hands)
		return (free(philosophers), free(fourchettes), 1);
	if (mutex_init(philo, fourchettes))
		return (free(philosophers), free(fourchettes), free(hands), 1);
	if (launch(philosophers, hands, philo, fourchettes))
		return (1);
	return (end(philosophers, hands, philo, fourchettes));
}
