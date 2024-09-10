#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigusr1(int sig)
{}
	printf("Received SIGUSR1\n");
}

void handle_sigusr2(int sig)
{
	printf("Received SIGUSR2\n");
}

int main()
{
	// Set up signal handlers
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_sigusr2);

	printf("Process ID: %d\n", getpid());

	// Loop indefinitely
	while (1) {
		pause(); // Wait for signals
	}
	return 0;
}

