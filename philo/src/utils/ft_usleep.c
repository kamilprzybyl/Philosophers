#include "../../inc/philo.h"

void	ft_usleep(useconds_t ms)
{
	unsigned long long res;

	res = timestamp() + ms;
	while (timestamp() <= res)
		usleep(50);
}
