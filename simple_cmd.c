#include "simpleshell.h"

char	*get_path_value(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp("PATH", env->key))
			return (env->value);
		env = env->link;
	}
	return (0);
}

char	**create_2d_array_from_env_list(t_env *env)
{
	int		i;
	char	*str;
	char	**env_arr;
	int		env_length;

	i = 0;
	env_length = ft_lstsize_env(env);
	env_arr = malloc((env_length + 1) * sizeof(char *));
	if (!env_arr)
		return (0);
	while (env)
	{
		str = NULL;
		str = ft_strjoin(str, env->key);
		if (env->value)
		{
			str = ft_strjoin(str, "=");
			str = ft_strjoin(str, env->value);
		}
		env_arr[i++] = ft_strdup(str);
		free(str);
		env = env->link;
	}
	env_arr[i] = 0;
	return (env_arr);
}

char	*get_paths(char *cmd, t_env *env)
{
	int		i;
	char	*path_value;
	char	**paths;
	char	*path;

	i = -1;
	path_value = get_path_value(env);
	if (!path_value)
		return (0);
	paths = ft_split(path_value, ":");
	if (!paths)
		return (0);
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!access(paths[i], X_OK))
		{
			path = ft_strdup(paths[i]);
			ft_free_arr(paths);
			return (path);
		}
	}
	ft_free_arr(paths);
	return (cmd);
}

void	simple_cmd(t_cmd *f_list, t_env *env, char *command
	, char **env_arr)
{
	if (f_list->cmd && f_list->cmd[0])
	{
		if (check_if_builtin(f_list))
			exit (g_exit_status);
		command = get_paths(f_list->cmd[0], env);
		if (!command)
		{
			ft_free_arr(env_arr);
			ft_printf("Shell: %s: No such file or directory\n",
				2, f_list->cmd[0]);
			exit(127);
		}
		g_exit_status = 0;
		if (execve(command, f_list->cmd, env_arr) == -1)
		{
			ft_printf("Shell: %s: command not found\n", 2, f_list->cmd[0]);
			free(command);
			ft_free_arr(env_arr);
			exit(127);
		}
	}
}
