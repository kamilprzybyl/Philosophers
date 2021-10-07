#include "../philo.h"

void	print_status(int nb, char *status)
{
	pthread_mutex_lock(&g_data.status_mutex);
	printf("%lli %i %s\n", timestamp(), nb + 1, status);
	pthread_mutex_unlock(&g_data.status_mutex);
}
