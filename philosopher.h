/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:34:49 by kscordel          #+#    #+#             */
/*   Updated: 2023/06/24 17:42:19 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int				nb_of_eat;	
}		t_philo;

typedef struct	s_hand
{
	pthread_mutex_t	*fourchette_G;
	pthread_mutex_t	*fourchette_D;
	char			*fourch_G;
	char			*fourch_D;
	char			*tab_fourch;
	t_philo			info;
	int				num_philo;
	pthread_mutex_t	*cycle;
}		t_hand;

int	ft_atoi(const char *nptr);
void	clear_mutex(pthread_mutex_t *fourchettes, int indice);

//les routines
void	*paire(void *arg);


#endif
