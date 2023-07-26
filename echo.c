#include "simpleshell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @env: A pointer to the environment list.
 * @key: The key of the environment variable to retrieve.
 * Return: The value of the environment variable if found, otherwise NULL.
 */
char	*_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (!_strcmp(env->key, key))
			return (env->value);
		env = env->link;
	}
	return (NULL);
}

/**
 * _setenv - Set the value of an environment variable.
 * @envr: A double pointer to the environment list.
 * @key: The key of the environment variable to set.
 * @value: The value to set for the environment variable.
 */
void	_setenv(t_env **envr, char *key, char *value)
{
	t_env	*env;

	env = *envr;
	while (env)
	{
		if (!_strcmp(env->key, key))
		{
			free(env->value);
			env->value = _strdup(value);
			break ;
		}
		env = env->link;
	}
	free(value);
	return ;
}

/**
 * change_dir_2 - Change the current working directory.
 * @envr: A double pointer to the environment list.
 * @v: A pointer to the t_vars structure.
 */
void	change_dir_2(t_env **envr, t_vars *v)
{
	if (v->tmp_str && !chdir(v->tmp_str))
	{
		v->command = getcwd(NULL, 0);
		if (v->command)
		{
			_setenv(envr, "OLDPWD", _strdup(_getenv(*envr, "PWD")));
			_setenv(envr, "PWD", v->command);
		}
	}
	else
	{
		g_exit_status = 1;
		perror(v->tmp_str);
	}
}

/**
 * check_cd_env - Check the arguments for the 'cd'
 * command and handle special cases.
 * @envr: A double pointer to the environment list.
 * @f_list: A pointer to the t_cmd structure representing the command.
 * @v: A pointer to the t_vars structure.
 * Return: 1 if the 'cd' command should exit early, 0 otherwise.
 */
int	check_cd_env(t_env **envr, t_cmd *f_list, t_vars *v)
{
	if (!f_list->cmd[1] || !_strcmp(f_list->cmd[1], "~"))
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (!_strcmp(f_list->cmd[1], "-"))
	{
		if (_getenv(*envr, "OLDPWD"))
		{
			v->tmp_str = _strdup(_getenv(*envr, "OLDPWD"));
			_printf("%s\n", 1, v->tmp_str);
		}
		else
		{
			_printf("Shell: : cd: OLDPWD not set\n", 2);
			return (1);
		}
		return (0);
	}
	else
		v->tmp_str = _strdup(f_list->cmd[1]);
	return (0);
}

/**
 * change_dir - Handle the 'cd' command and change
 * the current working directory.
 * @envr: A double pointer to the environment list.
 * @f_list: A pointer to the t_cmd structure representing the command.
 */
void	change_dir(t_env **envr, t_cmd *f_list)
{
	t_vars	v;

	v.tmp_str = NULL;
	if (!f_list->cmd[1] && !_getenv(*envr, "HOME"))
	{
		_printf("Shell: : cd: HOME not set\n", 2);
		return ;
	}
	else if (check_cd_env(envr, f_list, &v))
		return ;
	v.val = getcwd(NULL, 0);
	change_dir_2(envr, &v);
	free(v.tmp_str);
	free(v.val);
}

/**
 * check_cmd - Check and handle built-in commands (cd, exit, env).
 * @envr: A double pointer to the environment list.
 * @f_list: A pointer to the t_cmd structure representing the command.
 */
void	check_cmd(t_env **envr, t_cmd *f_list)
{
	if (f_list && !_strcmp(f_list->cmd[0], "cd"))
		change_dir(envr, f_list);
	if (f_list->cmd && f_list->cmd[0] && !_strcmp(f_list->cmd[0], "exit"))
		ft_exit(f_list->cmd, f_list);
	else if (lstsize_cmd(f_list) == 1 && f_list->cmd && f_list->cmd[0]
		&& !_strcmp(f_list->cmd[0], "env"))
		env_parsing(f_list->cmd, *envr);
}
