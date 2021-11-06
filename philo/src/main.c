#include "../inc/philo.h"

static	int	parse(int argc, char **argv, t_data *data)
{
	int	i;

	if ((argc != 5 && argc != 6))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]) || argv[i][0] == '-')
			return (1);
		if (ft_atoi(argv[i]) == -1 || ft_atoi(argv[i]) == 0)
			return (1);
		i++;
	}
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	return (0);
}

static int	init(t_data *data)
{
	int		i;
	long	time;

	pthread_mutex_init(&data->status, NULL);
	data->philo = malloc(sizeof(struct s_philo) * data->nb_of_philos);
	if (!data->philo)
		return (1);
	i = -1;
	time = timestamp();
	data->start = time;
	data->fed_philos = 0;
	while (++i < data->nb_of_philos)
	{
		data->philo[i].id = i;
		data->philo[i].last_meal = time;
		data->philo[i].meals = 0;
		pthread_mutex_init(&data->philo[i].fork, NULL);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data) == 1 || init(&data) != 0)
	{
		write(2, "error\n", 6);
		return (1);
	}
	launch_philos(&data);
	check_death(&data);
	join_threads(&data);
	// sleep(100);
	return (0);
}
