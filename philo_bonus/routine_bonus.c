#include "philosopher_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	sem_wait(philo->info->forks);
	printing_status(philo->info, philo->philo_id - 1, "has taken a fork");
	sem_wait(philo->info->eating_sem);
	printing_status(philo->info, philo->philo_id - 1, "is eating");
	philo->last_eat_time = ft_time();
	sem_post(philo->info->eating_sem);
	sleep_control(philo->info->eat_time, philo->info);
	philo->eat_count++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	*is_died(void *philosophers)
{
	t_philo	*p;
	t_data	*data;

	p = (t_philo *)philosophers;
	data = p->info;
	while (1)
	{
		sem_wait(data->eating_sem);
		if (ft_time() - p->last_eat_time > (long)data->die_time)
		{
			printing_status(data, p->philo_id - 1, "died");
			data->is_dead = 1;
			exit(1);
		}
		sem_post(data->eating_sem);
		if (data->is_dead)
			break ;
		if (p->eat_count >= data->must_eat && data->must_eat != -1)
			break ;
		usleep(1000);
	}
	return (0);
}