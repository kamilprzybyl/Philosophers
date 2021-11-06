#include "../inc/philo.h"

static void	*meal_loop(void *arg)
{
	int		i;
	int		j;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (data->philo[i].meals == data->meals_to_eat)
			data->fed_philos++;
		if (data->fed_philos == 5)
		{
			pthread_mutex_lock(&data->status);
			printf("%li Everyone has eaten enough\n",
				(timestamp() - data->start) / 1000);
			j = 0;
			while (j < data->nb_of_philos)
				pthread_detach(data->philo[j++].thread_id);
			return (0);
		}
		i++;
		if (i == data->nb_of_philos)
			i = 0;
	}
	return (NULL);
}

int	check_meals(t_data *data)
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &meal_loop, data) != 0)
		return (1);
	pthread_join(id, NULL);
	return (0);
}
