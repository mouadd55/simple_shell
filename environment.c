#include "simpleshell.h"

/**
 * split_string - Splits the input string into commands
 * and processes each command.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * @final_list: A pointer to the head of the final list of commands.
 * @envr: A pointer to a pointer to the head of the environment variables list.
 * @size: An integer flag indicating the number of commands in the final list.
 */
void	split_string(t_vars *v, t_cmd *final_list, t_env **envr, int size)
{
	v->tmp1 = _split_input(v->str);
	lexer(&v->tmp1);
	if (size == 1)
		check_cmd(envr, final_list);
	_destroy_list(&v->tmp1);
	free(v->str);
	v->str = NULL;
}

/**
 * print_env - Prints the environment variables.
 * @i: The number of arguments in the 'cmd' array.
 * @count: The number of 'env' occurrences in the 'cmd' array.
 * @env: A pointer to the environment list.
 */
void	print_env(int i, int count, t_env *env)
{
	if (i && i == count)
	{
		while (env)
		{
			if (env->value)
				_printf("%s=%s\n", 1, env->key, env->value);
			env = env->link;
		}
	}
}

/**
 * env_parsing - Handles the 'env' command and prints environment variables.
 * @cmd: A double pointer to an array of strings containing
 * the command arguments.
 * @env: A pointer to the environment list.
 */
void	env_parsing(char **cmd, t_env *env)
{
	t_vars	v;

	v.i = -1;
	v.count = 0;
	while (cmd[++v.i])
	{
		if (_strcmp(cmd[v.i], "env") == 0)
			v.count++;
		else if (v.count && cmd[v.i][0] == '-' && _strlen(cmd[v.i]) > 1)
		{
			g_exit_status = 1;
			_printf("env: illegal option -- %c\n", 2, cmd[v.i][1]);
			return;
		}
		else if (v.count && cmd[v.i][0] != '-')
		{
			g_exit_status = 127;
			_printf("env: %s: No such file or directory\n", 2, cmd[v.i]);
			return;
		}
	}
	print_env(v.i, v.count, env);
}

/**
 * _split_environment - Splits the environment array into
 * a linked list of t_env nodes.
 * @env: A double pointer to an array of strings containing
 * the environment variables.
 * Return: A pointer to the head of the environment list.
 */
t_env	*_split_environment(char **env)
{
	int		i;
	int		start;
	int		length;
	t_env	*envr;

	i = -1;
	envr = NULL;
	while (env[++i])
	{
		start = 0;
		length = _strlen(env[i]);
		while (env[i][start] != '=')
			start++;
		_lstadd_back_env(&envr, _lstnew_env(_substr(env[i], 0, start),
				_substr(env[i], start + 1, length)));
	}
	return (envr);
}
