#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int		ft_putchar(char c)
{
	return (write(1, &c, 1));
}

void	ft_putnbr(int nbr)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 1);
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar(nbr % 10 + '0');
}

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

static int	client_pid;

void	ft_decode(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void)context;

	if (client_pid)
		client_pid = info->si_pid;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &i, 1);
		bit = 0;
		i = 0;
		kill(client_pid, SIGUSR1);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_decode;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid = getpid();
	write(1, "pid: ", 6);
	ft_putnbr(pid);
	while (1)
	{
		pause ();
	}
	return (0);
 }
