#include "philosopher.h"

void	eat_the_spaghetti(t_philo *philosophers, time_t t1)
{
	pthread_mutex_lock(&(philosophers->data->time_meal));
	philosophers -> meal_time = ft_time();
	pthread_mutex_unlock(&(philosophers->data->time_meal));
	pthread_mutex_lock(&(philosophers->data->eating));
	philosophers -> i_ate += 1;
	pthread_mutex_unlock(&(philosophers->data->eating));
	if (is_died(philosophers))
		return ;
	printf("%ld %d is eating\n", ft_time() - t1, philosophers->name);
	if (is_eaten(philosophers))
		return ;
	sleep_control(philosophers->data->time_to_eat, philosophers);
	if (is_died(philosophers) || is_eaten(philosophers))
		return ;
}

void	take_forks(t_philo *philosophers, time_t t1)
{
	if (philosophers->name % 2)
		usleep(1000);
	pthread_mutex_lock(&philosophers->fork_r);
	if (is_died(philosophers) || is_eaten(philosophers))
	{
		pthread_mutex_unlock(&philosophers->fork_r);
		return ;
	}
	printf("%ld %d has taken a fork\n", ft_time() - t1, philosophers->name);
	if (philosophers->number_of_philos == 1)
	{
		do_for_one(philosophers, &(philosophers->fork_r));
		return ;
	}
	pthread_mutex_lock(&philosophers->left_philo->fork_r);
	if (is_died(philosophers) || is_eaten(philosophers))
	{
		unlock_forks(&philosophers->left_philo->fork_r, &philosophers->fork_r);
		return ;
	}
	printf("%ld %d has taken a fork\n", ft_time() - t1, philosophers->name);
	eat_the_spaghetti(philosophers, t1);
	unlock_forks(&philosophers->left_philo->fork_r, &philosophers->fork_r);
	start_sleeping(philosophers, t1);
}

void	do_for_one(t_philo *philosophers, pthread_mutex_t *fork)
{
	sleep_control(philosophers->data->time_to_die, philosophers);
	pthread_mutex_lock(&(philosophers->data->dying));
	philosophers->i_died = 1;
	pthread_mutex_unlock(&(philosophers->data->dying));
	pthread_mutex_unlock(fork);
}

void	start_sleeping(t_philo *philosophers, time_t t1)
{
	if (is_died(philosophers) || is_eaten(philosophers))
		return ;
	printf("%ld %d is sleeping\n", ft_time() - t1, philosophers->name);
	sleep_control(philosophers->data->time_to_sleep, philosophers);
	if (is_died(philosophers) || is_eaten(philosophers))
		return ;
	printf("%ld %d is thinking\n", ft_time() - t1, philosophers->name);
	sleep_control(1, philosophers);
	if (is_died(philosophers))
		return ;
}

void	unlock_forks(pthread_mutex_t *fork_l, pthread_mutex_t *fork_r)
{
	pthread_mutex_unlock(fork_l);
	pthread_mutex_unlock(fork_r);
}
