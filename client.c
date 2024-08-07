#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

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
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	send_to_server(int pid, char c)
{
	int	index;

	index = 0;
	
	while (index < 8)
	{
		if (c & (1 << index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (kill(pid, SIGUSR1) == -1 || kill(pid, SIGUSR2) == -1)
		{
		    perror("Error sending signal");
		    exit(1);
		}
		usleep(1000);
		index++;
	}
}

void	is_sent(int sig)
{
	(void)sig;
}	

int	main(int argc, char **argv)
{
	int	server_pid;
	int	index;
	char	*message;

	if (argc != 3)
	{
		write(1, "Usage: %%s <server_pid> <message>\n", 34);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	printf("server PID entered:%d\n",server_pid);
	message = argv[2];
	signal(SIGUSR1, is_sent);
	while (*message)
	{ 
		printf("Sending char: %c\n", *message);
		send_to_server(server_pid, *message);
		printf("Waiting for acknowledgment...\n");
		pause();
		printf("Acknowledgment received.\n");
		message++;
	}
	send_to_server(server_pid, '\0');
	return (0);	
}
