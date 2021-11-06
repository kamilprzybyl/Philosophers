#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				fed_philos;
	long			start;
	struct s_philo	*philo;
	pthread_mutex_t	status;
}				t_data;

struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals;
	long			last_meal;
	pthread_mutex_t	fork;
	t_data			*data;
};

int		launch_philos(struct s_data *data);
int		check_meals(struct s_data *data);
int		check_death(t_data *data);
int		join_threads(t_data *data);
void	print_status(int nb, char *status, t_data *data);
long	timestamp(void);
int		ft_atoi(const char *str);
int		is_number(char *s);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	ft_usleep(useconds_t ms);
void	free_philos(t_data *data);

#endif