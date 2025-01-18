#include "philosopher.h"

void	*i_am_thread(void *philosophers)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)philosophers;
	if (philo->data->philosophers_must_eat >= 1)
	{
		while (++i < philo->data->philosophers_must_eat)
			take_forks(philo, philo->time);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->dying));
		while (!(philo->i_died))
		{
			pthread_mutex_unlock(&(philo->data->dying));
			take_forks(philo, philo->time);
			pthread_mutex_lock(&(philo->data->dying));
		}
		pthread_mutex_unlock(&(philo->data->dying));
	}
	return (NULL);
}

void	sleep_control(time_t time, t_philo *philo)
{
	time_t	i;

	i = ft_time();
	pthread_mutex_lock(&(philo->data->dying));
	while (!(philo->i_died))
	{
		pthread_mutex_unlock(&(philo->data->dying));
		if ((ft_time() - i) >= time)
			return ;
		usleep(50);
		pthread_mutex_lock(&(philo->data->dying));
	}
	pthread_mutex_unlock(&(philo->data->dying));
}

void	destroy_mutexes(t_philo	*philosophers)
{
	int	i;

	i = -1;
	while (philosophers->name != 1)
		philosophers = philosophers->right_philo;
	pthread_mutex_destroy(&(philosophers->data->dying));
	pthread_mutex_destroy(&(philosophers->data->eating));
	pthread_mutex_destroy(&(philosophers->data->time_meal));
	if (philosophers->number_of_philos == 1)
	{
		pthread_mutex_destroy(&philosophers->fork_r);
		destroy_philos(&philosophers);
		return ;
	}
	while (++i < philosophers->number_of_philos
		&& philosophers->right_philo != NULL)
	{
		pthread_mutex_destroy(&philosophers->fork_r);
		philosophers = philosophers->right_philo;
	}
	destroy_philos(&philosophers);
}

void	destroy_philos(t_philo **philosophers)
{
	t_philo	*tmp;
	int		i;

	i = -1;
	free((*philosophers)->data);
	tmp = *philosophers;
	while (++i < (*philosophers)->number_of_philos)
	{
		tmp = (*philosophers)->right_philo;
		free (*philosophers);
		*philosophers = tmp;
	}
}

int	is_died(t_philo *philosophers)
{
	int				i;

	pthread_mutex_lock(&(philosophers->data->dying));
	i = philosophers->i_died;
	pthread_mutex_unlock(&(philosophers->data->dying));
	if (i == 1)
		return (1);
	i = -1;
	while (++i < philosophers->number_of_philos
		&& philosophers->right_philo != NULL)
	{
		pthread_mutex_lock(&(philosophers->data->time_meal));
		if (philosophers->data->time_to_die
			<= (ft_time() - (philosophers -> meal_time)))
		{
			pthread_mutex_unlock(&(philosophers->data->time_meal));
			pthread_mutex_lock(&(philosophers->data->dying));
			philosophers -> i_died = 1;
			pthread_mutex_unlock(&(philosophers->data->dying));
			return (1);
		}
		pthread_mutex_unlock(&(philosophers->data->time_meal));
		philosophers = philosophers -> right_philo;
	}
	return (0);
}
