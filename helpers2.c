#include "simpleshell.h"

/**
 * return_val - Get the value of the specified environment variable.
 * @envi: The name of the environment variable to retrieve.
 * Return: The value of the environment variable as a dynamically
 * allocated string, or NULL if the variable does not exist.
 */
char *return_val(char *envi)
{
	char *env;

	env = find_right_path(envi);
	if (env)
		return (env);
	return (0);
}

/**
 * exit_status_and_pid - Get the value of special tokens $? and $$.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * @var: The string representing the special token or environment variable.
 * Return: The value of the special token or environment variable as a dynamically
 * allocated string, or NULL if 'var' is not a special token or an
 * existing environment variable.
 */
char *exit_status_and_pid(t_info *vars, char *var)
{
	char c;
	char *str;

	c = *var;
	if (c != '?' && c != '$')
	{
		str = return_val(var);
		return (str);
	}
	if (c == '$')
		str = _itoa(vars->pid);
	else
		str = _itoa(vars->exit_status);
	return (str);
}
