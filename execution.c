#include "simpleshell.h"

int	check_if_builtin(t_cmd *final_list)
{
	int		i;
	char	**arr;
	char	*tmp;

	i = -1;
	tmp = strlower(final_list->cmd[0]);
	if (!ft_strcmp(tmp, "pwd"))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	arr = ft_split("cd env exit", " ");
	while (arr[++i])
	{
		if (final_list->cmd && final_list->cmd[0]
			&& !ft_strcmp(final_list->cmd[0], arr[i]))
		{
			ft_free_arr(arr);
			return (1);
		}
	}
	ft_free_arr(arr);
	return (0);
}

void	execute_commands(t_vars *v, t_env **env, int size)
{
	v->env_arr = create_2d_array_from_env_list(*env);
	v->child = fork();
	if (v->child < 0)
	{
		ft_free_arr(v->env_arr);
		perror("Shell: : fork");
	}
    else if (v->child == 0)
    {
    	signal(SIGINT, SIG_DFL);
	    signal(SIGQUIT, SIG_DFL);
	    if (v->final_list->fd_out == -1 && v->final_list->fd_in == -1)
	    	exit(g_exit_status);
	    if (v->final_list->cmd && !v->final_list->cmd[0])
	    	exit(0);
	    if (size == 1)
	    	simple_cmd(v->final_list, *env, v->command, v->env_arr);
    }
	v->command = NULL;
    ft_free_arr(v->env_arr);
}

void	execution(t_cmd *final_list, t_env **env, t_list **lst)
{
	t_vars	v;

	v.lst = *lst;
	v.final_list = final_list;
	v.count = lstsize_cmd(final_list);
	signal(SIGINT, SIG_IGN);
	if (final_list->cmd)
		execute_commands(&v, env, v.count);
	ft_destroy_list(lst);
	exit_by_signal();
	signal(SIGINT, &catching_signals);
}
