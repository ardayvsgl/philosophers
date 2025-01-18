#include "philosopher.h"

void	destroy_threads_exit(t_philo *philos)
{
	int	i;

	i = -1;
	if (philos->number_of_philos == 1)
	{
		pthread_join(philos->thread, NULL);
		return ;
	}
	while (++i < philos->number_of_philos && philos->right_philo != NULL)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->right_philo;
	}
	pthread_join(philos->thread, NULL);
	destroy_mutexes(philos);
}

void	add_to_struct(char **argv, t_philo **philosophers, int thread)
{
	t_philo	*a;

	a = ft_new(thread, argv);
	ft_add_back(philosophers, a);
}

int	if_i_am_dead(t_philo *philosophers)
{
	int	i;

	i = -1;
	while (++i < philosophers -> number_of_philos)
	{
		pthread_mutex_lock(&(philosophers->data->dying));
		if (philosophers -> i_died)
		{
			pthread_mutex_unlock(&(philosophers->data->dying));
			printf("%ld %d died\n",
				ft_time() - philosophers->time, philosophers->name);
			return (1);
		}
		pthread_mutex_unlock(&(philosophers->data->dying));
		philosophers = philosophers -> right_philo;
	}
	return (0);
}

int	is_eaten(t_philo *philosophers)
{
	int		i;
	int		t;
	t_philo	*philos;

	i = -1;
	t = 0;
	philos = philosophers;
	while (++i < philos -> number_of_philos)
	{
		if (philos->right_philo == NULL)
			break ;
		pthread_mutex_lock(&(philosophers->data->eating));
		if (philos -> i_ate == philos -> right_philo -> i_ate)
			t++;
		pthread_mutex_unlock(&(philosophers->data->eating));
		philos = philos -> right_philo;
	}
	if (t == philos -> number_of_philos
		&& philos->data->philosophers_must_eat == philos -> i_ate)
		return (1);
	return (0);
}

int	is_valid(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] <= '9' && argv[i][j] >= '0'))
				return (0);
		}
	}
	if (!(ft_atoi(argv[1])) || !(ft_atoi(argv[2]))
		|| !(ft_atoi(argv[3])) || !(ft_atoi(argv[4])))
		return (0);
	return (1);
}
