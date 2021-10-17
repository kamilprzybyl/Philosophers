#include "../inc/philo.h"

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
		g_data.meals_to_eat = 0;
	pthread_mutex_init(&g_data.status, NULL);
	g_data.philo = malloc(sizeof(t_philo) * g_data.nb_of_philos);
	if (!g_data.philo)
		return (1);
	i = -1;
	time = timestamp();
	g_data.start = timestamp();
	while (++i < g_data.nb_of_philos)
	{
		g_data.philo[i].id = i;
		g_data.philo[i].last_meal = time;
		g_data.philo[i].meals = 0;
		pthread_mutex_init(&g_data.philo[i].fork, NULL);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int	i;
	int	j;

	if ((argc != 5 && argc != 6) || init(argv) != 0)
	{
		write(1, "error\n", 6);
		return (1);
	}
	i = 0;
	while (i < g_data.nb_of_philos)
	{
		if (pthread_create(&g_data.philo[i].thread_id, NULL, &thread, &g_data.philo[i]) != 0)
			return (3);
		i++;
	}
	j = 0;
	while (j < g_data.nb_of_philos)
	{
		if (pthread_join(g_data.philo[j].thread_id, NULL) != 0)
			return (4);
		j++;
	}
	return (0);
}
