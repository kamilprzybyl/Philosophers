#include "../inc/philo.h"

static void	eat(int id, t_data *data)
{
	if (id % 2)
	{
		pthread_mutex_lock(&data->philo[id].fork);
		print_status(id, "has taken a fork", data);
		pthread_mutex_lock(&data->philo[(id + 1) % data->nb_of_philos].fork);
		print_status(id, "has taken a fork", data);
	}
	else
	{
		pthread_mutex_lock(&data->philo[(id + 1) % data->nb_of_philos].fork);
		print_status(id, "has taken a fork", data);
		pthread_mutex_lock(&data->philo[id].fork);
		print_status(id, "has taken a fork", data);
	}
	data->philo[id].last_meal = timestamp();
	print_status(id, "is eating", data);
	ft_usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->philo[id].fork);
	pthread_mutex_unlock(&data->philo[(id + 1) % data->nb_of_philos].fork);
	data->philo[id].meals++;
}

static void	take_a_nap(int id, t_data *data)
{
	print_status(id, "is sleeping", data);
	ft_usleep(data->time_to_sleep * 1000);
}

static void	think(int id, t_data *data)
{
	print_status(id, "is thinking", data);
}

static void	*philo(void *arg)
{
	struct s_philo	*philo;

	philo = (struct s_philo *)arg;
	if (philo->id % 2)
		ft_usleep(1);
	while (philo->data->meals_to_eat == -1
		|| philo->meals < philo->data->meals_to_eat)
	{
		eat(philo->id, philo->data);
		take_a_nap(philo->id, philo->data);
		think(philo->id, philo->data);
	}
	return (NULL);
}

int	launch_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread_id, NULL,
				&philo, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
