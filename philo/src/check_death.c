#include "../inc/philo.h"

static int	meal(int i, t_data *data)
{
	int	j;

	if (data->philo[i].meals == data->meals_to_eat)
		data->fed_philos++;
	if (data->fed_philos == 5)
	{
		pthread_mutex_lock(&data->status);
		printf("%li Everyone has eaten enough\n",
			(timestamp() - data->start) / 1000);
		usleep(1000);
		j = 0;
		while (j < data->nb_of_philos)
			pthread_detach(data->philo[j++].thread_id);
		return (0);
	}
	return (1);
}

static void	stupid_function(t_data *data, int id)
{
	int	j;

	pthread_mutex_lock(&data->status);
	data->death_lock = 1;
	printf("%li %i died\n", (timestamp() - data->start) / 1000, id + 1);
	usleep(1000);
	j = 0;
	while (j < data->nb_of_philos)
		pthread_detach(data->philo[j++].thread_id);
}

static void	*death_loop(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if ((timestamp() - data->philo[i].last_meal) / 1000
			> (long)data->time_to_die)
		{
			stupid_function(data, i);
			return (0);
		}
		if (!meal(i, data))
			return (0);
		i++;
		if (i == data->nb_of_philos)
			i = 0;
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &death_loop, data) != 0)
		return (1);
	pthread_join(id, NULL);
	return (0);
}
