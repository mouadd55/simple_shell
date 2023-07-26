#include "simpleshell.h"

void	catching_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
	}
}
