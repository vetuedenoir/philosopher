#include "../philosopher.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		signe;
	long	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * signe);
}

void	ft_usleep(int time)
{
	long	x;

	x = gettime();
	while (gettime() - x < time)
		usleep(50);
}

long gettime(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	//printf("\n time sec = %ld et time usec = %ld\n", time.tv_sec, time.tv_usec);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

int	timemsg(t_hand *hand, long lastmeal, char *str)
{
	if (gettime() - lastmeal > (long)hand->info.time_to_die)
	{
		sem_wait(hand->write);		
		printf("%ld %d %s\n", (gettime() - hand->t_debut)\
			/ 1000, hand->num_philo, "died");
		sem_post(hand->write);
		sem_post(hand->died);
		return (1);
	}
	sem_wait(hand->write);
	printf("%ld %d %s\n", (gettime() - hand->t_debut)\
		/ 1000, hand->num_philo, str);
	return (sem_post(hand->write), 0);
}
