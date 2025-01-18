#include "philosopher_bonus.h"

void	*i_am_process(t_philo *philo)
{
	philo->last_eat_time = ft_time();
	pthread_create(&philo->info->thread, NULL, &is_died, philo);
	if (philo->philo_id % 2 == 0)
		usleep(10000);
	while (!(philo->info->is_dead))
	{
		take_forks(philo);
		if (philo->eat_count >= philo->info->must_eat
			&& philo->info->must_eat != -1)
			break ;
		printing_status(philo->info, philo->philo_id - 1, "is sleeping");
		sleep_control(philo->info->sleep_time, philo->info);
		printing_status(philo->info, philo->philo_id - 1, "is thinking");
	}
	pthread_join(philo->info->thread, NULL);
	if (philo->info->is_dead)
		exit(1);
	exit(0);
}

void	create_philosophers(t_data *data, char **av, int ac)
{
	int	i;

	i = -1;
	data->philo_count = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->is_dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	sem_unlink("/eating_semaphore");
	sem_unlink("/printing_semaphore");
	sem_unlink("/forks");
	data->eating_sem = sem_open("/eating_semaphore", O_CREAT, S_IRWXU, 1);
	data->printing_sem = sem_open("/printing_semaphore", O_CREAT, S_IRWXU, 1);
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->philo_count);
	while (++i < data->philo_count)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].info = data;
		data->philos[i].philo_id = i + 1;
	}
}

void	create_processes(t_data *data)
{
	int		i;

	i = -1;
	data->start_time = ft_time();
	while (++i < data->philo_count)
	{
		data->philos[i].pid_no = fork();
		if (data->philos[i].pid_no == 0)
			i_am_process(&data->philos[i]);
		usleep(100);
	}
	destroy_processes_exit(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 6 || argc == 5)
	{
		if (!is_valid(argv))
			return (0);
		create_philosophers(&data, argv, argc);
		create_processes(&data);
	}
}