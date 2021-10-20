#include "../inc/philo.h"

void	ft_usleep(int length)
{
	long	time;

	time = timestamp();
	while (timestamp() < time + length)
		usleep(length);
}

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
	g_data.philo[id].last_meal = timestamp();
	print_status(id, "is eating");
	ft_usleep(g_data.time_to_eat * 1000);
	g_data.philo[id].meals++;
	pthread_mutex_unlock(&g_data.philo[id].fork);
	pthread_mutex_unlock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
}

void	*thread(void *arg)
{
	int	id;

	id = *(int *)arg; 
	while (g_data.meals_to_eat == -1 || g_data.philo[id].meals < g_data.meals_to_eat)
	{
		// if (timestamp() - philo->last_meal < g_data.time_to_die)
		// 	break ;
		eat(id);
		print_status(id, "is sleeping");
		ft_usleep(g_data.time_to_sleep * 1000);
		print_status(id, "is thinking");
	}
	// print_status(philo->id, "died");
	return (NULL);
}
