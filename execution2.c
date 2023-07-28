#include "simpleshell.h"

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
