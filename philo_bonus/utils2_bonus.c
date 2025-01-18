#include "philosopher_bonus.h"

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

void	sleep_control(long long time, t_data *data)
{
	long long	i;

	i = ft_time();
	while (!(data->is_dead))
	{
		if ((ft_time() - i) >= time)
			break ;
		usleep(50);
	}
}
