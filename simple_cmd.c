#include "simpleshell.h"

/**
 * get_path_value - Get the value of the "PATH" environment variable.
 * @env: The head of the t_env linked list.
 * Return: A pointer to the value of the "PATH" environment variable,
 *         or NULL if "PATH" is not found in the linked list.
 */
char	*get_path_value(t_env *env)
{
	while (env)
	{
		if (!_strcmp("PATH", env->key))
			return (env->value);
		env = env->link;
	}
	return (0);
}

/**
 * create_2d_array_from_env_list - Convert the t_env
 * linked list into a 2D array.
 * @env: The head of the t_env linked list.
 * Return: A pointer to a dynamically allocated 2D array
 * representing the environment variables,
 *         or NULL on failure.
 */
char	**create_2d_array_from_env_list(t_env *env)
{
	int		i;
	char	*str;
	char	**env_arr;
	int		env_length;

	i = 0;
	env_length = _lstsize_env(env);
	env_arr = malloc((env_length + 1) * sizeof(char *));
	if (!env_arr)
		return (0);
	while (env)
	{
		str = NULL;
		str = _strjoin(str, env->key);
		if (env->value)
		{
			str = _strjoin(str, "=");
			str = _strjoin(str, env->value);
		}
		env_arr[i++] = _strdup(str);
		free(str);
		env = env->link;
	}
	env_arr[i] = 0;
	return (env_arr);
}

/**
 * get_paths - Get the full path of the given command by
 * searching for it in the "PATH" environment variable.
 * @cmd: The command to search for in the "PATH".
 * @env: The head of the t_env linked list.
 * Return: A pointer to a dynamically allocated strin
 * containing the full path of the command,
 * or a pointer to the original command if it was not found in the "PATH".
 */
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
	paths = _split(path_value, ":");
	if (!paths)
		return (0);
	while (paths[++i])
	{
		paths[i] = _strjoin(paths[i], "/");
		paths[i] = _strjoin(paths[i], cmd);
		if (!access(paths[i], X_OK))
		{
			path = _strdup(paths[i]);
			_free_arr(paths);
			return (path);
		}
	}
	_free_arr(paths);
	return (cmd);
}

/**
 * simple_cmd - Execute a simple command (non-built-in)
 * with appropriate path handling.
 * @f_list: A pointer to the command node.
 * @env: The head of the t_env linked list.
 * @command: A pointer to the command path.
 * @env_arr: A pointer to the 2D array representing the environment variables.
 */
void	simple_cmd(t_cmd *f_list, t_env *env, char *command
	, char **env_arr)
{
	if (f_list->cmd && f_list->cmd[0])
	{
		if (check_if_builtin(f_list))
			exit(0);
		command = get_paths(f_list->cmd[0], env);
		if (!command)
		{
			_free_arr(env_arr);
			_printf("Shell: %s: No such file or directory\n",
				2, f_list->cmd[0]);
			exit(127);
		}
		if (execve(command, f_list->cmd, env_arr) == -1)
		{
			_printf("Shell: %s: command not found\n", 2, f_list->cmd[0]);
			free(command);
			_free_arr(env_arr);
			exit(127);
		}
	}
}
