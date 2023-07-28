#include "simpleshell.h"

char *return_val(char *envi)
{
	char *env;

	env = find_right_path(envi);
	if (env)
		return (env);
	return (0);
}

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
