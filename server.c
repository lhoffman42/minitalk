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

void	sig_decode(int sig, siginfo_t *info, void *context)
{
	static char c;
	static int bit_count;

	(void)context;
	if (sig == SIGUSR1)
		c = (1 << bit_count);
	bit_count++;	
	if (bit_count == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
	if(kill(info->si_pid, SIGUSR1) == -1)
		perror("error confirming submission");
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_decode;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		printf("setting up signal handler failed\n");
	}
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("\n\n\n[Server's Process ID]: %d\n\n\n",getpid());
	while (1)
		pause();
	return (0);
}
