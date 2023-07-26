#include "simpleshell.h"

void	get_command(t_vars *v, t_env **env, char **env_arr)
{
	v->command = get_paths(v->final_list->cmd[0], *env);
	if (!v->command)
	{
		ft_free_arr(env_arr);
		ft_printf("Shell: : %s: No such file or directory\n",
			2, v->final_list->cmd[0]);
		exit(127);
	}
}

void	send_command_to_execve(t_vars *v, t_env **env, char **env_arr)
{
	if (check_if_builtin(v->final_list))
	{
		ft_builtins(*env, v->final_list);
		exit (g_exit_status);
	}
	else if (execve(v->command, v->final_list->cmd, env_arr) == -1)
	{
		ft_printf("Shell: : %s: command not found\n", 2,
			v->final_list->cmd[0]);
		free(v->command);
		ft_free_arr(env_arr);
		exit(127);
	}
}
