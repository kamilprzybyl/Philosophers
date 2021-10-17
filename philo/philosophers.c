#include "philo.h"

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
	usleep(g_data.time_to_eat * 1000);
	pthread_mutex_unlock(&g_data.philo[id].fork);
	pthread_mutex_unlock(&g_data.philo[(id + 1) % g_data.nb_of_philos].fork);
}

void	*thread(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (timestamp() - philo->last_meal < g_data.time_to_die)
	{
		eat(philo->id);
		print_status(philo->id, "is sleeping");
		usleep(g_data.time_to_sleep * 1000);
		print_status(philo->id, "is thinking");
	}
	print_status(philo->id, "died");
	return (NULL);
}
