/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:32:59 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 18:18:57 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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

int	launch(pthread_t *philosophers, t_hand *hands, t_philo data, \
	pthread_mutex_t *f)
{
	int	i;

	i = 0;
	while (i < data.num_of_philos)
	{
		if (pthread_create(&philosophers[i], NULL, &routine, &hands[i]) != 0)
		{
			write(2, "erreur : pthread_creat\n", 23);
			while (--i >= 0)
			{
				if (pthread_join(philosophers[i], NULL) != 0)
					write(2, "erreur : pthread_join\n", 22);
			}
			return (free(philosophers), free(hands), \
				clear_mutex(f, data.num_of_philos + 2), free(f), 1);
		}
		i += 1;
	}
	return (0);
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
