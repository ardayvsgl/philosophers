#include "philosopher.h"

int	ft_atoi(const char *str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str++ - '0';
		if ((num * sign) < -2147483648)
			return (0);
		if ((num * sign) > 2147483647)
			return (-1);
	}
	return ((int)(num) *sign);
}

t_philo	*ft_new(int name, char **argv)
{
	t_philo	*a;

	a = malloc(sizeof(t_philo));
	if (!a)
		return (NULL);
	a -> name = name;
	a -> right_philo = NULL;
	a -> left_philo = NULL;
	a -> data = NULL;
	a -> i_ate = 0;
	a -> i_died = 0;
	a -> number_of_philos = ft_atoi(argv[1]);
	a -> meal_time = ft_time();
	a -> time = ft_time();
	return (a);
}

time_t	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_add_back(t_philo **philosophers, t_philo *a)
{
	t_philo	*tmp;

	if (!a)
		return ;
	if (!(*philosophers))
	{
		*philosophers = a;
		return ;
	}
	tmp = ft_last(*philosophers);
	tmp -> right_philo = a;
}

t_philo	*ft_last(t_philo *philosophers)
{
	if (!philosophers)
		return (0);
	while (philosophers -> right_philo)
		philosophers = philosophers -> right_philo;
	return (philosophers);
}
