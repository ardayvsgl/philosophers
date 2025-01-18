#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philosophers_must_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	dying;
	pthread_mutex_t	time_meal;
}	t_data;

typedef struct s_philo
{
	int				name;
	time_t			time;
	pthread_mutex_t	fork_r;
	int				number_of_philos;
	int				i_ate;
	int				i_died;
	time_t			meal_time;
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
	t_data			*data;
	pthread_t		thread;
}	t_philo;

int		ft_atoi(const char *str);
time_t	ft_time(void);
t_philo	*ft_new(int name, char **argv);
void	ft_add_back(t_philo **philosophers, t_philo *a);
t_philo	*ft_last(t_philo *philosophers);

void	take_forks(t_philo *philosophers, time_t t1);
void	eat_the_spaghetti(t_philo *philosophers, time_t t1);
void	do_for_one(t_philo *philosophers, pthread_mutex_t *fork);
void	start_sleeping(t_philo *philosophers, time_t t1);
void	start_thinking(t_philo *philosophers, time_t t1);
int		is_died(t_philo *philosophers);
int		if_i_am_dead(t_philo *philosophers);
int		is_eaten(t_philo *philosophers);
void	destroy_threads_exit(t_philo *philos);
void	destroy_mutexes(t_philo	*philosophers);
void	add_to_struct(char **argv, t_philo **philosophers,
			int thread);
int		is_valid(char **argv);
void	sleep_control(time_t time, t_philo *philo);
void	*i_am_thread(void *philosophers);
void	unlock_forks(pthread_mutex_t *fork_l, pthread_mutex_t *fork_r);
void	destroy_philos(t_philo **philosophers);

#endif