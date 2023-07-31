#include "../philosopher.h"

int	ft_isitdead(t_hand *hand, long lastmeal)
{
	long t;

	t = gettime() - lastmeal;
	if (t > (long)hand->info.time_to_die)
	{
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", (gettime() - hand->t_debut)\
				/ 1000, hand->num_philo, "is died");
			pthread_mutex_unlock(hand->ecrire);
		}
		pthread_mutex_unlock(hand->is_dead);
		return (1);
	}
	return (0);
}

int	timemsg(t_hand *hand, long lastmeal, char *str)
{
	char d;

	d = 0;
	if (gettime() - lastmeal > (long)hand->info.time_to_die)
	{
		pthread_mutex_lock(hand->is_dead);
		if (!(*hand->dead))
		{
			*hand->dead = 1;
			pthread_mutex_lock(hand->ecrire);
			printf("%ld %d %s\n", (gettime() - hand->t_debut)\
				/ 1000, hand->num_philo, "died");
			pthread_mutex_unlock(hand->ecrire);
		}
		return (pthread_mutex_unlock(hand->is_dead), 1);
	}
	pthread_mutex_lock(hand->is_dead);
	d = *hand->dead;
	pthread_mutex_unlock(hand->is_dead);
	if (d)
		return (1);
	pthread_mutex_lock(hand->ecrire);
	printf("%ld %d %s\n", (gettime() - hand->t_debut)\
		/ 1000, hand->num_philo, str);
	return (pthread_mutex_unlock(hand->ecrire), 0);
}

int	ft_eat(t_hand *hand, long *nb_of_eat, long *lastmeal)
{
	if (timemsg(hand, *lastmeal, "is eating"))
		return (1);
	*lastmeal = gettime();
	if (*nb_of_eat > 0)
		*nb_of_eat = *nb_of_eat - 1;
	ft_usleep(hand->info.time_to_eat);
	return (0);
}

