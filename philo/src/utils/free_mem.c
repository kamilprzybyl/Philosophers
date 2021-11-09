#include "../../inc/philo.h"

void	free_mem(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
		pthread_mutex_destroy(&(data->philo[i++].fork));
	pthread_mutex_destroy(&(data->status));
	free(data->philo);
}
