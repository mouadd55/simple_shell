#include "simpleshell.h"

/**
 * catching_signals - Signal handler function to catch
 * and handle specific signals.
 * @sig: The signal number received by the signal handler.
 * Description:  Signal handler function to catch and handle specific
 * signals, mainly SIGINT (Ctrl+C).
 */
void	catching_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
	}
}

/**
 * check_if_builtin - Check if a command is a built-in command.
 * @final_list: A pointer to the command node.
 * Return: 1 if the command is a built-in command, 0 otherwise.
 */
int	check_if_builtin(t_cmd *final_list)
{
	int		i;
	char	**arr;

	i = -1;
	arr = _split("cd env exit", " ");
	while (arr[++i])
	{
		if (final_list->cmd && final_list->cmd[0]
			&& !_strcmp(final_list->cmd[0], arr[i]))
		{
			_free_arr(arr);
			return (1);
		}
	}
	_free_arr(arr);
	return (0);
}

/**
 * execute_commands - Execute the commands in the final command list.
 * @v: A pointer to the t_vars structure containing shell variables.
 * @env: A pointer to the t_env structure representing
 * the environment variables.
 * @size: The number of commands in the final list.
 * Description: Executes a list of commands using forked child processes.
 */
void	execute_commands(t_vars *v, t_env **env, int size)
{
	while (v->final_list)
	{
		v->env_arr = create_2d_array_from_env_list(*env);
		v->child = fork();
		if (v->child < 0)
		{
			_free_arr(v->env_arr);
			perror("Shell: : fork");
			return;
		}
		v->command = NULL;
		if (v->child == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		if (v->final_list->cmd && !v->final_list->cmd[0])
			exit(0);
		if (size == 1)
			simple_cmd(v->final_list, *env, v->command, v->env_arr);
	}
		_free_arr(v->env_arr);
		v->final_list = v->final_list->link;
	}
}

/**
 * execution - Execute the command(s) in the final command list.
 * @final_list: A pointer to the head of the command linked list.
 * @env: A pointer to the t_env structure representing
 * the environment variables.
 * @lst: A pointer to the linked list.
 * Description: Executes commands in a final command list while
 * handling signals and child processes.
 */
void	execution(t_cmd *final_list, t_env **env, t_list **lst)
{
	t_vars	v;
	int	wait_return;

	v.lst = *lst;
	v.final_list = final_list;
	v.count = lstsize_cmd(final_list);
	signal(SIGINT, SIG_IGN);
	if (final_list->cmd)
		execute_commands(&v, env, v.count);
	_destroy_list(lst);
	wait_return = 0;
	while (wait_return != -1)
		wait_return = wait(NULL);
	signal(SIGINT, &catching_signals);
}
