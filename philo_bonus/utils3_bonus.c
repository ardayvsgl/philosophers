#include "philosopher_bonus.h"

void	destroy_processes_exit(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->philo_count)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->philo_count)
				kill(data->philos[i].pid_no, 15);
			break ;
		}
		i++;
	}
	sem_unlink("/eating_semaphore");
	sem_unlink("/printing_semaphore");
	sem_unlink("/forks");
	sem_close(data->eating_sem);
	sem_close(data->printing_sem);
	sem_close(data->forks);
	free(data->philos);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

void	printing_status(t_data *data, int philo_num, char *state)
{
	sem_wait(data->printing_sem);
	if (ft_strncmp("died", state, 4) == 0 && data->is_dead == 0)
	{
		data->is_dead = 1;
		printf("%lld ", ft_time() - data->start_time);
		printf("%d ", philo_num + 1);
		printf("%s\n", state);
		return ;
	}
	if (!(data->is_dead))
	{
		printf("%lld ", ft_time() - data->start_time);
		printf("%d ", philo_num + 1);
		printf("%s\n", state);
	}
	sem_post(data->printing_sem);
	return ;
}
