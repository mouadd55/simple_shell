#include "simpleshell.h"

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
