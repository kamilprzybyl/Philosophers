#include "../inc/philo.h"

static	int	parse(int argc, char **argv)
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
	return (0);
}

static int	init(char **argv)
{
	int		i;
	long	time;

	g_data.nb_of_philos = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_data.meals_to_eat = ft_atoi(argv[5]);
	else
		g_data.meals_to_eat = -1;
	pthread_mutex_init(&g_data.status, NULL);
	g_data.philo = malloc(sizeof(t_philo) * g_data.nb_of_philos);
	if (!g_data.philo)
		return (1);
	i = -1;
	time = timestamp();
	g_data.start = time;
	while (++i < g_data.nb_of_philos)
	{
		g_data.philo[i].id = i;
		g_data.philo[i].last_meal = time;
		g_data.philo[i].meals = 0;
		pthread_mutex_init(&g_data.philo[i].fork, NULL);
	}
	return (0);
}

static void	*check_death()
{
	int i = 0;
	while (1)
	{
		if ((timestamp() - g_data.philo[i].last_meal) / 1000 > (unsigned long long)g_data.time_to_die)
		{
			print_status(i, "died");
			exit(0);
		}
		i++;
		if (i == g_data.nb_of_philos)
			i = 0;
	}
	return (NULL);
}

int	launch_philos()
{
	int	i;
	int	j;

	i = 0;
	while (i < g_data.nb_of_philos)
	{
		if (pthread_create(&g_data.philo[i].thread_id, NULL, &philo, &g_data.philo[i].id) != 0)
			return (1);
		i++;
	}
	j = 0;
	while (j < g_data.nb_of_philos)
	{
		if (pthread_join(g_data.philo[j].thread_id, NULL) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{

	pthread_t		id;

	if (parse(argc, argv) == 1 || init(argv) != 0)
	{
		write(2, "error\n", 6);
		return (1);
	}
	// int i = 0;
	// while (1)
	// {
	// 	if ((timestamp() - g_data.philo[i].last_meal) / 1000 > (unsigned long long)g_data.time_to_die)
	// 	{
	// 		print_status(i, "died");
	// 		return (0);
	// 	}
	// 	i++;
	// 	if (i == g_data.nb_of_philos)
	// 		i = 0;
	// }
	if (pthread_create(&id, NULL, &check_death, NULL) != 0)
		return (1);
	return (launch_philos());
}
