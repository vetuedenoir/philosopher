#include "../philosopher.h"

t_philo	init(char **argv, int argc)
{
	t_philo	philo;
	
	if (argc < 5)
		return (philo.num_of_philos = 0, philo);
	philo.num_of_philos = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]) * 1000;
	philo.time_to_eat = ft_atoi(argv[3]) * 1000;
	philo.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo.nb_of_eat = ft_atoi(argv[5]);
	else
		philo.nb_of_eat = -1;
	if (philo.num_of_philos <= 0 || philo.time_to_die <= 0 || 
		philo.time_to_eat <= 0 || philo.time_to_sleep <= 0)
		return (printf("wrong arg \n"),\
			philo.num_of_philos = 0, philo);
	return (philo);
}

t_hand	creat_hand(t_philo philo)
{
	t_hand	hand;
	
	sem_unlink("died");
	sem_unlink("fourchettes");
	sem_unlink("write");
	hand.died = sem_open("died", O_CREAT, 600, 1);
	hand.fourchettes = sem_open("fourchettes", O_CREAT, 600,\
		philo.num_of_philos);
	hand.write = sem_open("write", O_CREAT, 600, 1);
	hand.info = philo;
	hand.num_philo = 0;
	hand.t_debut = gettime();
	hand.sync = 500;
	return (hand);
}

void	kill_all(pid_t *list_pid, int index)
{
	while (--index >= 0)
		kill(SIGSTOP, list_pid[index]);
}

int	launch(t_philo philo, pid_t *list_pid)
{
	t_hand hand;
	pid_t	pid;
	int	i;
	
	hand = creat_hand(philo);
	pid = 1;
	i = 0;
	while (++i <= philo.num_of_philos)
	{
		if (pid != 0)
		{
			pid = fork();
			printf("j ai fork %d\n", i);
		}
		if (pid == -1)
			return (kill_all(list_pid, i - 1), 1);
		if (pid == 0)
		{
			free(list_pid);
			routine(hand, i);
		}
		printf(" i = %d\n", i);
		if (pid != 0)
			list_pid[i - 1] = pid;
	}
	if (pid != 0)
		monitoring(philo, list_pid, hand);
	if (pid != 0)
	{
		printf("salut \n");
		i = 0;
		while (list_pid[i])
		{
			waitpid(list_pid[i++], NULL, 0);
			printf("waitpid %d\n", list_pid[i - 1]);
		}
	}
	sem_destroy(hand.died);
	sem_destroy(hand.write);
	sem_destroy(hand.fourchettes);
	printf("j ai wait \n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	pid_t		*list_pid;
	
	philo = init(argv, argc);
	if (philo.num_of_philos == 0)
		return (1);
	list_pid = malloc(sizeof(pid_t) * (philo.num_of_philos + 1));
	if (!list_pid)
		return (1);
	list_pid = memset(list_pid, 0, sizeof(pid_t) * (philo.num_of_philos + 1));
	printf("list_pid pointeur = %p\n", list_pid);
	return  (launch(philo, list_pid));
}