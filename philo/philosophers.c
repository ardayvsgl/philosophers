#include "philosopher.h"

void	use_mutex_for_forks(t_philo *philosophers)
{
	t_philo	*tmp;

	tmp = philosophers;
	pthread_mutex_init(&(philosophers -> data -> eating), NULL);
	pthread_mutex_init(&(philosophers -> data -> dying), NULL);
	pthread_mutex_init(&(philosophers -> data -> time_meal), NULL);
	while (philosophers->right_philo
		&& (philosophers->name < philosophers->right_philo->name))
	{
		pthread_mutex_init(&(philosophers -> fork_r), NULL);
		philosophers = philosophers->right_philo;
	}
	pthread_mutex_init(&(philosophers -> fork_r), NULL);
	philosophers = tmp;
}

void	put_them_in_table(char **argv, t_philo **philosophers)
{
	t_philo	*tmp;

	if (ft_atoi(argv[1]) != 1)
	{
		tmp = *philosophers;
		while ((*philosophers) && (*philosophers)-> right_philo)
		{
			(*philosophers)-> right_philo -> left_philo = (*philosophers);
			(*philosophers)-> right_philo -> data = (*philosophers)->data;
			(*philosophers) = (*philosophers)-> right_philo;
		}
		(*philosophers)-> right_philo = tmp;
		tmp -> left_philo = *philosophers;
		*philosophers = tmp;
	}
}

void	create_philosophers(char **argv, t_philo **philosophers, int argc)
{
	int		i;

	i = 0;
	while (++i <= ft_atoi(argv[1]))
		add_to_struct(argv, philosophers, i);
	(*philosophers)->data = malloc(sizeof(t_data));
	(*philosophers)->data->time_to_die = ft_atoi(argv[2]);
	(*philosophers)->data->time_to_eat = ft_atoi(argv[3]);
	(*philosophers)->data->time_to_sleep = ft_atoi(argv[4]);
	(*philosophers)->data->philosophers_must_eat = -1;
	if (argc == 6)
		(*philosophers)->data->philosophers_must_eat = ft_atoi(argv[5]);
	put_them_in_table(argv, philosophers);
	use_mutex_for_forks(*philosophers);
}

void	create_threads(char *argv, t_philo *philosophers)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv) && philosophers != NULL)
	{
		pthread_create(&philosophers->thread, NULL,
			&i_am_thread, philosophers);
		philosophers = philosophers->right_philo;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;

	philosophers = NULL;
	if (argc == 6 || argc == 5)
	{
		if (!is_valid(argv))
			return (0);
		create_philosophers(argv, &philosophers, argc);
		create_threads(argv[1], philosophers);
		while (1)
		{
			if (is_died(philosophers)
				&& if_i_am_dead(philosophers))
			{
				destroy_threads_exit(philosophers);
				break ;
			}
			else if (is_eaten(philosophers))
			{
				destroy_threads_exit(philosophers);
				break ;
			}
		}
	}
}
