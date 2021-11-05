#include "../../inc/philo.h"

void	ft_usleep(useconds_t ms)
{
	long	time;

	time = timestamp();
	while (timestamp() < time + ms)
		usleep(50);
}
