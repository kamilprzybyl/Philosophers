#include "philo.h"

// __thread const char* thread_name;
// pthread_mutex_t		mutex[];
// void	test(int i)
// {
// 	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
// 	{
// 		state[i] = EATING;
// 		up(s[i]);
// 	}
// }

// void	*put_forks(int i)
// {
// 	pthread_mutex_lock(mutex);
// 	state[i] = THINKING;
// 	test(LEFT);
// 	test(RIGHT);
// 	pthread_mutex_unlock(mutex);
// }

// void	take_forks(t_data *data)
// {
// 	pthread_mutex_lock(data->fork[0]);
// 	state[i] = HUNGRY;
// 	test(i);
// 	pthread_mutex_unlock(mutex);
// 	down(s[i]);
// }

// void	think(t_data data)
// {
// 	// thread_name = __func__;
// 	gettimeofday(&data.tv, &data.tz);
// 	printf("%ld %s is thinking\n", data.tv.tv_sec * 1000, );
// 	sleep(1);
// }

// void	eat(t_data data)
// {

// }

void	*thread(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (1)
	{
		print_status(philo->nb, "is thinking");
		if (philo->nb == 2)
			sleep(2);
		print_status(philo->nb, "is eating");
		usleep(g_data.time_to_eat * 1000);
		print_status(philo->nb, "is sleeping");
		usleep(g_data.time_to_sleep * 1000);
	}
	return (NULL);
}
