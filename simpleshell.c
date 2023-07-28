#include "simpleshell.h"

/**
 * catching_signals - Signal handler for SIGINT.
 * @sig: The signal number.
 * Return: nothing
 */
void catching_signals(int sig)
{
	(void)sig;
	signal(SIGINT, catching_signals);
	_printf("\n$ ", 1);
	fflush(stdout);
}

/**
 * find_right_path - Find the value of an environment variable.
 * @name: The name of the environment variable to search for.
 * Return: The value of the environment variable as a dynamically
 * allocated string, or NULL if the variable does not exist.
 */
char *find_right_path(const char *name)
{
	char *str;
	char *key;
	char *val;
	char **env;
	size_t length;

	length = _strlen(name);
	for (env = environ; *env; ++env)
	{
		str = _strdup(*env);
		key = strtok(str, "=");
		if (!key)
		{
			free(str);
			return (0);
		}
		if (_strlen(key) != length)
		{
			free(str);
			continue;
		}
		if (!_strcmp(name, str))
		{
			key = strtok(NULL, "=");
			val = _strdup(key);
			free(str);
			return (val);
		}
		free(str);
	}
	return (0);
}

/**
 * execution - Execute a command with its arguments.
 * @arguments: The array of command and its arguments.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * @buf: The input buffer containing the command and arguments.
 * Return: nothing.
 */
void execution(char **arguments, t_info *vars, char *buf)
{
	char *command;
	int flag;

	if (!(*arguments) || !arguments)
		return;
	command = arguments[0];
	vars->cmd = command;
	if (is_builtin_ar_not(vars, arguments) == 1)
		return;
	flag = check_if_file_exist(command);
	if (flag == NON_PERMISSIONS)
	{
		vars->exit_status = 126;
		vars->nbr_error = 13;
		what_error(vars);
		return;
	}
	if (flag == 1)
	{
		execution2(command, arguments, vars, buf);
		return;
	}
	if (execute_command(command, arguments, buf, vars) == 1)
		return;
	vars->path_value = where_is_the_cmd(command);
	if (vars->path_value)
	{
		execution2(vars->path_value, arguments, vars, buf);
		free(vars->path_value);
		return;
	}
	vars->exit_status = 127;
	vars->nbr_error = 132;
	what_error(vars);
}

/**
 * current_path - Check the order of the path
 * @path: PATH to check
 * @vars: General infos
 **/
void current_path(char *path, t_info *vars)
{
	vars->current_path = 0;

	if (path == NULL)
		return;

	if (path[0] == ':')
		vars->current_path = 1;
}

/**
 * everything_starts_here - Main shell loop.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 */
void everything_starts_here(t_info *vars)
{
	char *path;
	char *buff;
	char **args;

	signal(SIGINT, catching_signals);
	while (1)
	{
		if (vars->interactive == INTERACTIVE)
			_printf("$ ", 1);
		path = find_right_path("PATH");
		current_path(path, vars);
		vars->env = path;
		buff = take_input();
		if (!buff)
		{
			if (vars->interactive == INTERACTIVE)
				_printf("exit\n", 1);
			else
				_printf("", 1);
			free(path);
			break;
		}
		vars->count_cmd++;
		if (buff[0] != '\n')
		{
			args = _split(buff, " \t\n");
			vars->args = args;
			vars->buf = buff;
			tokenization(vars, args);
			execution(args, vars, buff);
			_free_arr(args);
		}
		free(path);
		free(buff);
	}
}

/**
 * main - The main function that initializes and runs the shell.
 * @ac: The number of command-line arguments.
 * @av: An array of strings containing the command-line arguments.
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	int exit_status;
	t_info *vars;

	vars = malloc(sizeof(t_info));
	if (!vars)
	{
		perror(av[0]);
		exit(1);
	}
	vars->ac = ac;
	vars->av = av;
	vars->pid = getpid();
	vars->count_cmd = 0;
	vars->exit_status = 0;
	vars->interactive = isatty(STDIN) == INTERACTIVE;
	everything_starts_here(vars);
	exit_status = vars->exit_status;
	free(vars);
	return (exit_status);
}
