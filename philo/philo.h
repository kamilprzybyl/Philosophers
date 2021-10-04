#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define HUNGRY 0
# define EATING 1
# define THINKING 2
# define LEFT (i - 1) % 3
# define RIGHT (i + 1) % 3

typedef struct s_rules
{
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_must_meals;
}				t_rules;

typedef struct s_data
{
	t_rules			rules;
	struct timeval	tv;
	struct timezone	tz;
	pthread_mutex_t	*fork;
}				t_data;

int		ft_atoi(const char *str);

#endif