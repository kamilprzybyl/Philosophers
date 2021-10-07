#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

# define HUNGRY 0
# define EATING 1
# define THINKING 2
# define LEFT (i - 1) % 3
# define RIGHT (i + 1) % 3

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_id;
	int				nb;
	int				meals;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	t_philo			philo[250];
	pthread_mutex_t	status_mutex;
}				t_data;

void		*thread(void *philo);
void		print_status(t_data *data, int id, char *status);
long long	timestamp(void);
int			ft_atoi(const char *str);

#endif