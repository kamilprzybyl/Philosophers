#include "../philo.h"

long long	timestamp(void)
{
	struct timeval	tv;
	// struct timezone	tz;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
