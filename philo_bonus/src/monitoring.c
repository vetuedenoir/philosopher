/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:33:06 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/23 18:03:08 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	kill_all(pid_t *list_pid, int index)
{
	while (--index >= 0)
		kill(SIGKILL, list_pid[index]);
}

void	*monitor(void *arg)
{
	t_hand	*hand;
	int		i;

	hand = (t_hand *)arg;
	i = 0;
	sem_wait(hand->died);
	while (hand->list_pid[i])
	{
		if (kill(hand->list_pid[i], SIGKILL))
			perror("kill");
		i++;
	}
	sem_post(hand->died);
	sem_post(hand->alive);
	usleep(10000);
	return (NULL);
}

void	monitoring(t_philo philo, pid_t *list_pid, t_hand hand)
{
	pthread_t	moniteur;
	t_hand		*hands;

	hands = malloc(sizeof(t_hand));
	*hands = hand;
	hands->list_pid = list_pid;
	if (pthread_create(&moniteur, NULL, &monitor, \
		hands) != 0)
	{
		write(2, "erreur : pthread_creat\n", 23);
		kill_all(list_pid, philo.num_of_philos);
		return ;
	}
	pthread_join(moniteur, NULL);
	sem_close(hands->alive);
	sem_close(hands->died);
	sem_close(hands->write);
	sem_close(hands->fourchettes);
	free(hands);
}
