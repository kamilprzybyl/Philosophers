#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals;
	long			last_meal;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	long			start;
	t_philo			*philo;
	pthread_mutex_t	status;
}				t_data;

t_data	g_data;

void	*thread(void *philo);
void	print_status(int nb, char *status);
long	timestamp(void);
int		ft_atoi(const char *str);

#endif