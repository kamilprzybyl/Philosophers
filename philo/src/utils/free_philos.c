#include "../../inc/philo.h"

void	free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->philo[i].fork);
		free(&data->philo[i]);
		i++;
	}
}
