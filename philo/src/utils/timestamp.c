#include "../../inc/philo.h"

unsigned long long	timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000 * 1000 + te.tv_usec);
}
