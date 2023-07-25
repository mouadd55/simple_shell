#include "simpleshell.h"

void	catching_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
        printf("Shell: ");
	}
}

void	exit_by_signal(void)
{
	int	wait_return;
	int	status;

	wait_return = 0;
	while (wait_return != -1)
		wait_return = wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			g_exit_status = WTERMSIG(status) + 128;
		}
	}
}
