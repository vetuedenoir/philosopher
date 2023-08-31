#include "../philosopher.h"

void	*monitor(void *arg)
{
	t_hand	*hand;
	int	i;
	
	
	
	hand = (t_hand*)arg;
	i = 0;
	printf("list_pid monitor pointeur = %p\n", hand->list_pid);
	sem_wait(hand->died);
	printf("\nwhat the HEEEEEEEELLLLLLLLLLLL!!!!!!!!\n");
	sem_wait(hand->died);
	printf("\nIS GOING ON BRO ????????????????\n");
	while (hand->list_pid[i])
	{
		if (kill(hand->list_pid[i], SIGSTOP))
			perror("kill");
		printf("i kill pid > %d\n", hand->list_pid[i]);
		i++;
	}
	sem_post(hand->died);
	sem_post(hand->died);
	ft_usleep(10000);
	sem_destroy(hand->died);
	sem_destroy(hand->write);
	sem_destroy(hand->fourchettes);
	
	free(hand->list_pid);
	exit(0);
	return (NULL);
}


void	monitoring(t_philo philo, pid_t *list_pid, t_hand hand)
{
	pthread_t	moniteur;
	t_hand		*hands;

	int	i;
	i = 0;
	hands = malloc(sizeof(t_hand));
	*hands = hand;
	while (list_pid[i])
		printf("pid %d\n", list_pid[i++]);
	hands->list_pid = list_pid;
	if (pthread_create(&moniteur, NULL, &monitor,\
		hands) != 0)
	{
		write(2, "erreur : pthread_creat\n", 23);
		kill_all(list_pid, philo.num_of_philos);
		return ;
	}
	pthread_detach(moniteur);
}
