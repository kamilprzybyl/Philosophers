#include "philo.h"

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

// void	take_forks(int i)
// {
// 	pthread_mutex_lock(mutex);
// 	state[i] = HUNGRY;
// 	test(i);
// 	pthread_mutex_unlock(mutex);
// 	down(s[i]);
// }

void	think(t_data data, int i)
{
	gettimeofday(&data.tv, &data.tz);
	printf("%ld %d is thinking\n", data.tv.tv_sec * 1000, i);
}

void	eat(t_data data, int i)
{
	gettimeofday(&data.tv, &data.tz);
	printf("%ld %d is eating\n", data.tv.tv_sec * 1000, i);
	usleep(data.rules.time_to_eat);
}

void	*philo(void *i)
{
	// while (1)
	// {
	// 	think();
	// 	take_forks();
	// 	eat();
	// 	put_forks();
	// }
	printf("I am philosopher number %d\n", *(int *)i);
	sleep(1);
	return (NULL);
}

int	init(t_data *data, char **argv)
{
	data->rules.nb_of_philos = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->rules.nb_of_must_meals = ft_atoi(argv[5]);
	else
		data->rules.nb_of_must_meals = 0;
	return (0);
}

int		main(__attribute__ ((unused)) int argc, char **argv)
{
	int			i;
	int			j;
	int			x;
	pthread_t	*thread;
	t_data		data;

	if ((argc != 5 && argc != 6) || init(&data, argv) != 0)
	{
		write(1, "error\n", 6);
		return (EXIT_FAILURE);
	}
	data.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.rules.nb_of_philos);
	if (!data.fork)
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data.rules.nb_of_philos);
	if (!thread)
		return (2);
	i = 0;
	while (i < data.rules.nb_of_philos)
	{
		if (pthread_create(&thread[i], NULL, &philo, &i) != 0)
			return (3);
		i++;
	}
	j = 0;
	while (j < data.rules.nb_of_philos)
	{
		if (pthread_join(thread[j], NULL) != 0)
			return (4);
		j++;
	}
	x = 0;
	while (x < data.rules.nb_of_philos)
		pthread_mutex_destroy(&data.fork[x]);
	return (0);
}
