#include "simpleshell.h"

int	check_if_builtin(t_cmd *final_list)
{
	int		i;
	char	**arr;

	i = -1;
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

int	fork_protection(t_vars *v, t_env **env)
{
	v->env_arr = create_2d_array_from_env_list(*env);
	v->child = fork();
	if (v->child < 0)
	{
		ft_free_arr(v->env_arr);
		perror("Shell: : fork");
		return (1);
	}
	v->command = NULL;
	return (0);
}

void	execute_commands(t_vars *v, t_env **env, int size)
{
	while (v->final_list)
	{
		if (fork_protection(v, env))
			return ;
		if (v->child == 0)
		{
        	signal(SIGINT, SIG_DFL);
	        signal(SIGQUIT, SIG_DFL);
	        if (v->final_list->cmd && !v->final_list->cmd[0])
	        	exit(0);
	        if (size == 1)
	        	simple_cmd(v->final_list, *env, v->command, v->env_arr);
        }
		ft_free_arr(v->env_arr);
		while ((v->lst) && ft_strcmp((v->lst)->type, "PIPE"))
		{
			(v->lst) = (v->lst)->link;
			if ((v->lst) && !ft_strcmp((v->lst)->type, "PIPE"))
			{
				(v->lst) = (v->lst)->link;
				break ;
			}
		}
		v->final_list = v->final_list->link;
	}
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
