#include "../../inc/philo.h"

void	print_status(int nb, char *status, t_data *data)
{
	pthread_mutex_lock(&data->status);
	printf("%li %i %s\n", (timestamp() - data->start) / 1000, nb + 1, status);
	pthread_mutex_unlock(&data->status);
}
