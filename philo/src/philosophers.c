#include "../inc/philo.h"

static void	eat(int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&g_data.philo[id].fork);
		print_status(id, "has taken a fork");
		pthread_mutex_lock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
		print_status(id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
		print_status(id, "has taken a fork");
		pthread_mutex_lock(&g_data.philo[id].fork);
		print_status(id, "has taken a fork");
	}
	print_status(id, "is eating");
	ft_usleep(g_data.time_to_eat * 1000);
	g_data.philo[id].last_meal = timestamp();
	pthread_mutex_unlock(&g_data.philo[id].fork);
	pthread_mutex_unlock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
	g_data.philo[id].meals++;
}

void	take_a_nap(int id)
{
	print_status(id, "is sleeping");
	ft_usleep(g_data.time_to_sleep * 1000);
}

void	think(int id)
{
	print_status(id, "is thinking");
}

void	*thread(void *arg)
{
	int	id;

	id = *(int *)arg;
	while (g_data.meals_to_eat == -1 || g_data.philo[id].meals < g_data.meals_to_eat)
	{
		eat(id);
		take_a_nap(id);
		think(id);
	}
	return (NULL);
}
