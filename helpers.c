#include "simpleshell.h"

/**
 * get_value - Get the value of an environment variable or special token.
 * @info: Pointer to the 't_info' struct containing shell variables.
 * @nbr: Pointer to the current position in the input 'arr'.
 * @arr: Pointer to the input string.
 * Return: The value of the environment variable or special token
 * as a dynamically allocated string.
 */
char *get_value(t_info *info, int *nbr, char *arr)
{
	int start;
	int after;
	int before;
	char *value;

	start = *nbr;
	start++;
	value = exit_status_and_pid(info, arr + start);
	if (!value)
	{
		arr = _strcpy(arr, "");
		return (arr);
	}
	before = _strlen(arr);
	after = _strlen(value) + 1;
	arr = _re_alloc(arr, before, after);
	arr = _strcpy(arr, value);
	free(value);
	*nbr = start;
	return (arr);
}

/**
 * expanding - Expand environment variables and special tokens in a string.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * @var: The string to be expanded.
 * Return: The expanded string with environment variables and
 * special tokens replaced by their values.
 */
char *expanding(t_info *vars, char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '$' && var[i + 1])
			var = get_value(vars, &i, var);
		i++;
	}
	return (var);
}

/**
 * take_input - Read input from standard input (stdin).
 * Return: Pointer to the input string, or NULL if EOF is encountered.
 */
char *take_input()
{
	int bytes;
	char *input;
	size_t length;

	input = 0;
	bytes = getline(&input, &length, stdin);
	if (bytes == EOF)
	{
		free(input);
		return (0);
	}
	return (input);
}

/**
 * tokenization - Perform tokenization and expansion on an array of strings.
 * @vars: Pointer to the 't_info' struct containing shell variables.
 * @args: The array of strings to be tokenized and expanded.
 */
void tokenization(t_info *vars, char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		args[i] = expanding(vars, args[i]);
		i++;
	}
}
