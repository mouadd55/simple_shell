#include "simpleshell.h"

char *find_exact_error(t_info vars)
{
	int i;
	t_err errors[] = {
		{"No such file or directory", 3},
		{"Permission denied", 13},
		{"not found", 132},
		{"Illegal number", 133}
	};

    i = 0;
	while (i < 4)
    {
		if (vars.nbr_error == errors[i].nbr)
			return (errors[i].error);
        i++;
    }
	return ("");
}

void more_errors(t_info *vars, char *more)
{
	int size_nbr;
    int size_extra;
    int length_of_error;
	char *error, *nbr;
    char *str1, *str2;

	nbr = NULL;
	error = find_exact_error(*vars);
	nbr = _itoa(vars->count_cmd);
	size_nbr = _strlen(nbr);
	length_of_error = _strlen(vars->av[0]);
	size_extra = _strlen(more);
	str1 = malloc(length_of_error + size_nbr + 3);
	str1 = _strcpy(str1, vars->av[0]);
	str1 = _strjoin(str1, ": ");
	str1 = _strjoin(str1, nbr);
	str2 = malloc(_strlen(error) + size_extra + 3);
	str2 = _strcpy(str2, error);
	str2 = _strjoin(str2, ": ");
	str2 = _strjoin(str2, more);
	error = build_error_message(str1, vars->cmd, str2, ": ");
	_printf("%s", 2, error);
	free(error);
	free(nbr);
	free(str1);
	free(str2);
}

void print_env(void)
{
	int i;
	char **str;

    i = 0;
    str = environ;
	while (str[i])
	{
		_printf("%s\n", 1, str[i]);
        i++;
	}
}

void ft_exit(t_info *vars, char **args)
{
    int status;
	int exit_status;

	status = 1;
	if (args[1])
		status = exit_args(vars, args[1]);
	if (!status)
		return;
	exit_status = vars->exit_status;
	_free_arr(args);
	free(vars->env);
	free(vars->buf);
	free(vars);
	exit(exit_status);
}

int is_builtin_ar_not(t_info *vars, char **args)
{
    if (!_strcmp(vars->cmd, "exit"))
    {
        ft_exit(vars, args);
        return (1);
    }
    else if (!_strcmp(vars->cmd, "env"))
    {
        print_env();
        return (1);
    }
	return (0);
}

