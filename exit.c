#include "simpleshell.h"

/**
 * sign_case2 - Helper function for handling exit command cases
 * with specific conditions.
 *              Checks if the command has special cases for exit.
 * @cmd: An array of strings containing the command and its arguments.
 * Return: 1 if the command has a special case, 0 otherwise.
 */
int	sign_case2(char **cmd)
{
	if (!_strcmp(cmd[1], "-0") && cmd[2] == 0)
	{
		_printf("exit\n", 1);
		exit(0);
	}
	else if (cmd[2] && _atoi(cmd[1]) == 0 && _atoi(cmd[2]) == 0)
	{
		_printf("exit\nShell: : exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

/**
 * sign_case - Handles the exit command cases with a sign (+ or -).
 *             Checks if the argument has a sign and validates
 *             the numeric argument.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * @cmd: An array of strings containing the command and its arguments.
 * Return: 1 if there is an error with the exit command, 0 otherwise.
 */
int	sign_case(t_vars *v, char **cmd)
{
	if (sign_case2(cmd))
		return (1);
	else if (cmd[v->i][0] == '+')
	{
		v->str = _itoa(_atoi(cmd[v->i]));
		if (_strcmp(cmd[v->i] + 1, v->str))
		{
			_printf("exit\nShell: : exit: %s: numeric argument required\n", 2,
				cmd[v->i]);
			free(v->str);
			exit(255);
		}
		if (!cmd[v->i + 1])
		{
			_printf("exit\n", 1);
			free(v->str);
			exit(_atoi(cmd[v->i]));
		}
		free(v->str);
	}
	return (0);
}

/**
 * check_if_digit - Checks if the given argument is
 * a valid numeric argument for the exit command.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * @cmd: An array of strings containing the command and its arguments.
 * Return: 1 if the argument is not a valid numeric argument, 0 otherwise.
 */
int	check_if_digit(t_vars *v, char **cmd)
{
	if (_isdigit(cmd[v->i]))
	{
		v->flag++;
		v->str = _itoa(_atoi(cmd[v->i]));
		if (sign_case(v, cmd))
		{
			free(v->str);
			v->str = NULL;
			return (1);
		}
		else if (_strcmp(cmd[v->i], v->str))
		{
			_printf("exit\nShell: : exit: %s: numeric argument required\n", 2,
				cmd[v->i]);
			free(v->str);
			v->str = NULL;
			exit(255);
		}
	}
	return (0);
}

/**
 * exit_errors - Handles errors for the exit command.
 *        Checks if the arguments provided to the exit command are valid.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * @cmd: An array of strings containing the command and its arguments.
 * Return: 1 if there is an error with the exit command, 0 otherwise.
 */
int	exit_errors(t_vars *v, char **cmd)
{
	if (check_if_digit(v, cmd))
		return (1);
	if (v->flag == 0)
	{
		_printf("exit\nShell: : exit: %s: numeric argument required\n", 2,
			cmd[v->i]);
		if (v->str)
		{
			free(v->str);
			v->str = NULL;
		}
		exit(255);
	}
	else if ((v->flag == 2 && v->i == 2) || (v->flag == 1 && v->i == 2))
	{
		v->j++;
		_printf("exit\nShell: : exit: too many arguments\n", 2);
	}
	if (v->str)
	{
		free(v->str);
		v->str = NULL;
	}
	return (0);
}

/**
 * ft_exit - Executes the exit command, terminating the shell.
 *           Checks if the arguments provided to the exit command are valid.
 * @cmd: An array of strings containing the command and its arguments.
 * @final: A pointer to the head of the final list of commands
 * (used to check if it is the last command).
 */
void	ft_exit(char **cmd, t_cmd *final)
{
	t_vars	v;

	v.i = 0;
	v.j = 0;
	v.flag = 0;
	while (cmd && cmd[++v.i])
	{
		if (!_strcmp("-9223372036854775808", cmd[v.i]))
		{
			_printf("exit\n", 1);
			exit(255);
		}
		if (exit_errors(&v, cmd))
			return;
	}
	if (final && !final->link && !final->prev && v.j == 0)
	{
		if (v.flag == 1)
		{
			_printf("exit\n", 1);
			exit(_atoi(cmd[1]));
		}
		_printf("exit\n", 1);
		exit(255);
	}
}
