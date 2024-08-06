#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	
	sign = 1;
	res = 0;
	while (*str == ' ' ||( *str >= '\t' &&  *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str + '0');
		str++;
	}
	return (res * sign);
}

void	send_to_server(int pid, char *str)
{
	
}

int	main(int argc, char **argv)
{
	int	pid;
	char	*str;

	if (argc < 3)
		printf("too few arguments");
	if (argc > 3)
		printf("too many arguments");
	pid = ft_atoi(argv[1]);
	str = argv[2];
	send_to_server(pid, str);
	return (0);	
}
