#include "../inc/philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
