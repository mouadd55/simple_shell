#include "simpleshell.h"

/**
 * has_x_permission - Check if the file has executable permission.
 * @file_name: The name of the file to check.
 * Return: 1 if the file has executable permission, -1 if it doesn't,
 * -2 if an error occurred.
 */
int has_x_permission(char *file_name)
{
	struct stat strcutt;

	if (!stat(file_name, &strcutt))
	{
		if (strcutt.st_mode & X_OK)
			return (1);
		else
			return (-1);
	}
	return (-2);
}

/**
 * execute_command - Execute a command with the specified arguments.
 * @cmd: The command to execute.
 * @args: An array of strings representing the command arguments.
 * @buf: The buffer containing the input command.
 * @info: The t_info struct containing information about the shell.
 * Return: 1 if the command is executed successfully, 0 otherwise.
 */
int execute_command(char *cmd, char **args, char *buf, t_info *info)
{

	if (!info->current_path)
		return (0);
	if (has_x_permission(cmd) == 1)
	{
		execution2(cmd, args, info, buf);
		return (1);
	}
	return (0);
}

/**
 * check_if_file_exist - Check if the file exists and has x permission.
 * @file: The name of the file to check.
 * Return: 1 if the file exists and has executable permission,
 * -1 if it doesn't, -2 if an error occurred.
 */
int check_if_file_exist(char *file)
{
	int i;
	int size;

	size = _strlen(file);
	for (i = 0; i < size; i++)
		if (file[i] == '/')
			return (has_x_permission(file));
	return (-2);
}


/**
 * execution2 - Execute a command using execve and wait
 * for the child process to finish.
 * @cmd: The command to execute.
 * @args: An array of strings representing the command arguments.
 * @vars: The t_info struct containing information about the shell.
 * @buf: The buffer containing the input command.
 * Return: nothing
 */
void execution2(char *cmd, char **args, t_info *vars, char *buf)
{
	int exit_status;
	pid_t child;

	child = fork();
	if (child == 0)
	{
		execve(cmd, args, environ);
		perror("./sh");
		_free_arr(args);
		if (vars->path_value)
		{
			free(vars->path_value);
			vars->path_value = 0;
		}
		free(buf);
		free(vars);
		exit(1);
	}
	else if (child > 0)
	{
		waitpid(child, &exit_status, 0);
		if (WIFEXITED(exit_status))
			vars->exit_status = WEXITSTATUS(exit_status);
	}
}
