#include "simpleshell.h"

/**
 * where_is_the_cmd - Find the full path of the executable command.
 * @file: The name of the command to search for.
 * Return: A pointer to the full path of the executable command if found,
 * or NULL if the command is not found or doesn't have executable permission.
 */
char *where_is_the_cmd(char *file)
{
	int size;
	char *key;
	char *str;
	char *place;
	char *tmp_value;

	place = find_right_path("PATH");
	if (!place)
		return (0);
	key = strtok(place, ":");
	size = _strlen(file) + 2;
	str = malloc(size * sizeof(char));
	str = _strcpy(str, "/");
	str = _strjoin(str, file);
	while (key)
	{
		tmp_value = malloc(_strlen(key) + size);
		tmp_value = _strcpy(tmp_value, key);
		tmp_value = _strjoin(tmp_value, str);
		if (has_x_permission(tmp_value) == 1)
		{
			free(place);
			free(str);
			return (tmp_value);
		}
		key = strtok(0, ":");
		free(tmp_value);
	}
	free(str);
	free(place);
	return (0);
}
