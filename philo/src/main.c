#include "../inc/philo.h"

void	free_philos(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_of_philos)
	{
		pthread_mutex_destroy(&g_data.philo[i].fork);
		free(&g_data.philo[i]);
		i++;
	}
}

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
	g_data.nb_of_philos = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_data.meals_to_eat = ft_atoi(argv[5]);
	else
		g_data.meals_to_eat = -1;
	return (0);
}

static int	init(void)
{
	int		i;
	long	time;

	pthread_mutex_init(&g_data.status, NULL);
	g_data.philo = malloc(sizeof(t_philo) * g_data.nb_of_philos);
	if (!g_data.philo)
		return (1);
	i = -1;
	time = timestamp();
	g_data.start = time;
	g_data.feed_philos = 0;
	while (++i < g_data.nb_of_philos)
	{
		g_data.philo[i].id = i;
		g_data.philo[i].last_meal = time;
		g_data.philo[i].meals = 0;
		pthread_mutex_init(&g_data.philo[i].fork, NULL);
	}
	return (0);
}

static int	launch_philos(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_of_philos)
	{
		if (pthread_create(&g_data.philo[i].thread_id, NULL,
				&philo, &g_data.philo[i].id) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	join_philos(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_of_philos)
	{
		if (pthread_join(g_data.philo[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*death_loop()
{
	int	i;

	i = 0;
	while (1)
	{
		if ((timestamp() - g_data.philo[i].last_meal) / 1000
			> (long)g_data.time_to_die)
		{
			pthread_mutex_lock(&g_data.status);
			printf("%li %i died\n", (timestamp() - g_data.start) / 1000, i + 1);
			exit(0);
		}
		i++;
		if (i == g_data.nb_of_philos)
			i = 0;
	}
	return (NULL);
}

void	*meal_loop()
{
	int	i;

	i = 0;
	while (1)
	{
		if (g_data.philo[i].meals == g_data.meals_to_eat)
			g_data.feed_philos++;
		if (g_data.feed_philos == 5)
		{
			pthread_mutex_lock(&g_data.status);
			printf("%li Everyone has eaten enough\n", (timestamp() - g_data.start) / 1000);
			exit(0);
		}
		i++;
		if (i == g_data.nb_of_philos)
			i = 0;
	}
	return (NULL);
}

static int	check_death()
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &death_loop, NULL) != 0)
		return (1);
	return (0);
}

static int	check_meals()
{
	pthread_t	id;

	if (pthread_create(&id, NULL, &meal_loop, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (parse(argc, argv) == 1 || init() != 0)
	{
		write(2, "error\n", 6);
		return (1);
	}
	check_death();
	check_meals();
	launch_philos();
	join_philos();
	free_philos();
	pthread_mutex_unlock(&g_data.status);
	return (0);
}
