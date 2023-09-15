/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:32:57 by kscordel          #+#    #+#             */
/*   Updated: 2023/09/14 16:55:37 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	end(t_hand hand, pid_t *list_pid, pid_t pid, t_philo philo)
{
	int	i;

	i = 0;
	if (pid != 0)
	{
		monitoring(philo, list_pid, hand);
		i = 0;
		while (list_pid[i])
			waitpid(list_pid[i++], NULL, 0);
	}
	free(list_pid);
	return (0);
}

int	launch(t_philo philo, pid_t *list_pid)
{
	t_hand	hand;
	pid_t	pid;
	int		i;

	hand = creat_hand(philo);
	pid = 1;
	i = 0;
	while (++i <= philo.num_of_philos)
	{
		if (pid != 0)
		{
			pid = fork();
		}
		if (pid == -1)
			return (kill_all(list_pid, i - 1), 1);
		if (pid == 0)
		{
			free(list_pid);
			routine(hand, i);
		}
		if (pid != 0)
			list_pid[i - 1] = pid;
	}
	return (end(hand, list_pid, pid, philo));
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	pid_t	*list_pid;

	philo = init(argv, argc);
	if (philo.num_of_philos == 0)
		return (1);
	list_pid = malloc(sizeof(pid_t) * (philo.num_of_philos + 1));
	if (!list_pid)
		return (1);
	list_pid = memset(list_pid, 0, sizeof(pid_t) * (philo.num_of_philos + 1));
	return (launch(philo, list_pid));
}
