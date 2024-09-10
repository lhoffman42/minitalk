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
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

void    receive_ack(int sig)
{
    (void)sig;
}

void	send_to_server(int pid, int i)
{
	int	bit;

	bit = 0;

	while (bit < 8)
	{
		if (i & (0x80 >> bit))
		{
			kill(pid, SIGUSR1);
			printf("1 sent\n");
		}
		else
		{
			kill(pid, SIGUSR2);
			printf("0 sent\n");
		}
		usleep(500);
		pause(); // Warte auf Signal vom Server
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
    struct sigaction	sa;

	if (argc != 3)
	{
		write(1, "Error: Wrong Format! Try: ./client <PID> <MESSAGE>\n", 51);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	printf("PID: %d\n", pid);

    // Signalhandler für Bestätigung einrichten
    sa.sa_handler = receive_ack;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

	i = 0;
	while (*argv[2])
	{
		send_to_server(pid, argv[2][i]);
        pause(); // Warte auf Bestätigung vom Server
		i++;
	}
	send_to_server(pid, '\0');
	return (0);
}