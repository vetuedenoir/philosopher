/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:32:59 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/23 20:59:51 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

t_philo	init(char **argv, int argc)
{
	t_philo	philo;
	if (argc < 5)
		return (0)
	philo.number_of_philosopher = argv[1];
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.nb_of_eat = ft_atoi(argv[5]);
	else
		philo.nb_of_eat = -1;
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_philo 		philo;
	pthread_t		*philosopher;
	pthread_mutex_t	*fourchette;

	philo = init(argv, argc);
	if (philo == 0)
		return (printf("wrong arg \n"), 0);
	philosopher = malloc(sizeof(pthread_t) * philo.number_of_philosopher);
	if (!philosopher)
		return (printf("erreur malloc\n")0);
	fourchette = malloc(sizeof(pthread_mutex_t) * philo.number_of_philosopher);
	if (!fourchette)
		return (printf("erreur malloc\n")0);
	
	
	
}
