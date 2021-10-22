#include "../inc/philo.h"

static void	eat(int id)
{
	if (timestamp() - g_data.philo[id].last_meal > g_data.time_to_die)
	{
		g_data.philo[id].dead = 1;
		print_status(id, "died");
		return ;
	}
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
	g_data.philo[id].last_meal = timestamp();
	print_status(id, "is eating");
	usleep(g_data.time_to_eat * 1000);
	g_data.philo[id].meals++;
	pthread_mutex_unlock(&g_data.philo[id].fork);
	pthread_mutex_unlock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
}

void	take_a_nap(int id)
{
	print_status(id, "is sleeping");
	usleep(g_data.time_to_sleep * 1000);
}

void	think(int id)
{
	print_status(id, "is thinking");
}

void	*thread(void *arg)
{
	int	id;

	id = *(int *)arg; 
	while (!g_data.philo[id].dead && (g_data.meals_to_eat == -1 || g_data.philo[id].meals < g_data.meals_to_eat))
	{
		eat(id);
		take_a_nap(id);
		think(id);
	}
	return (NULL);
}
