#include "simpleshell.h"

/**
 * _isdigit - Check if a char represents a valid integer.
 * @c: The character to be checked.
 * Return: 1 if the char represents a valid integer, 0 otherwise.
 */
int	_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * check_if_arg_has_an_alpha - Check if a string contains
 * any alphabetic characters.
 * @s: The string to be checked.
 * Return: 1 if the string contains an alphabetic character, 0 otherwise.
 */
int check_if_arg_has_an_alpha(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (_isdigit(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * exit_args - Process and validate the argument provided to the exit command.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * @nbr: The argument string provided to the 'exit' command.
 * Return: 0 if nbr is not a valid integer or exceeds the range, 1 otherwise.
 */
int exit_args(t_info *vars, char *nbr)
{
	int digit;

	digit = _atoi(nbr);
	if (digit < 0 || check_if_arg_has_an_alpha(nbr))
	{
		vars->nbr_error = 133;
		vars->exit_status = 2;
		more_errors(vars, nbr);
		return (0);
	}
	if (digit <= 255)
		vars->exit_status = digit;
	else
		vars->exit_status = digit % 256;
	return (1);
}


/**
 * build_error_message - Build an error message from multiple
 * parts with separators.
 * @part1: First part of the error message.
 * @part2: Second part of the error message.
 * @part3: Third part of the error message.
 * @between: The separator to be used between each part.
 * Return: Pointer to the built error message.
 */
char *build_error_message(char *part1, char *part2, char *part3, const char *between)
{
	char *str;
	int size_str1;
	int size_str2;
	int size_str3;
	int size_sep;

	size_str1 = size_str2 = size_str3 = size_sep = 0;
	if (part1)
		size_str1 = _strlen(part1);
	else
		part1 = "";
	if (part2)
		size_str2 = _strlen(part2);
	else
		part2 = "";
	if (part3)
		size_str3 = _strlen(part3);
	else
		part3 = "";
	if (between)
		size_sep = _strlen(between);
	else
		between = "";
	str = malloc(size_str1 + size_str2 + size_sep + size_str3 + size_sep + 2);
	if (!str)
		return (0);
	str = _strcpy(str, part1);
	str = _strjoin(str, (char *)between);
	str = _strjoin(str, part2);
	str = _strjoin(str, (char *)between);
	str = _strjoin(str, part3);
	str = _strjoin(str, "\n");
	return (str);
}

/**
 * what_error - Print an error message based on the command execution.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * Return: nothing.
 */
void what_error(t_info *vars)
{
	char *str;
	char *nbr;
	char *error;
	int length_of_nbr;
	int length_of_error;

	nbr = NULL;
	error = find_exact_error(*vars);
	nbr = _itoa(vars->count_cmd);
	length_of_nbr = _strlen(nbr);
	length_of_error = _strlen(vars->av[0]);
	str = malloc(length_of_error + length_of_nbr + 3);
	str = _strcpy(str, vars->av[0]);
	str = _strjoin(str, ": ");
	str = _strjoin(str, nbr);
	error = build_error_message(str, vars->cmd, error, ": ");
	_printf("%s", 2, error);
	free(error);
	free(nbr);
	free(str);
}
