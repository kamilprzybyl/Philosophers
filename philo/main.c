#include "philo.h"

static int	init(t_data *data, char **argv)
{
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = 0;
	return (0);
}

int		main(int argc, char **argv)
{
	int			i;
	int			j;
	t_data		data;
	t_philo		*philo;

	if ((argc != 5 && argc != 6) || init(&data, argv) != 0)
	{
		write(1, "error\n", 6);
		return (EXIT_FAILURE);
	}
	// data.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.rules.nb_of_philos);
	// if (!data.fork)
	// 	return (1);
	// thread = (pthread_t *)malloc(sizeof(pthread_t) * data.rules.nb_of_philos);
	// if (!thread)
	// 	return (2);
	philo = data.philo;
	i = 0;
	while (i < data.nb_of_philos)
	{
		philo[i].nb = i;
		if (pthread_create(&philo[i].thread_id, NULL, &thread, &philo[i]) != 0)
			return (3);
		i++;
	}
	j = 0;
	while (j < data.nb_of_philos)
	{
		if (pthread_join(philo[j].thread_id, NULL) != 0)
			return (4);
		j++;
	}
	return (0);
}
