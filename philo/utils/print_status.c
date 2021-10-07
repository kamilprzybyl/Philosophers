#include "../philo.h"

void	print_status(t_data *data, int nb, char *status)
{
	pthread_mutex_lock(&data->status_mutex);
	// if (!(rules->dieded))
	// {
	printf("%lli %i %s\n", timestamp(), nb + 1, status);
		// printf("%lli ", timestamp());
		// printf("%i ", id + 1);
		// printf("%s\n", status);
	// }
	pthread_mutex_unlock(&data->status_mutex);
	return ;
}
