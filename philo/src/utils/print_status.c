#include "../../inc/philo.h"

void	print_status(int nb, char *status)
{
	pthread_mutex_lock(&g_data.status);
	printf("%li %i %s\n", (timestamp() - g_data.start) / 1000, nb + 1, status);
	pthread_mutex_unlock(&g_data.status);
}
