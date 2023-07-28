#include "simpleshell.h"

/**
 * _strlen - Calculate the length of a null-terminated string.
 * @str: A pointer to the null-terminated string.
 * Return: The length of the string (excluding the null terminator).
 */
size_t	_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

/**
 * _putchar - Write a character to a file descriptor.
 * @ch: The character to be written.
 * @fd: The file descriptor where the character will be written.
 */
void	_putchar(char ch, int fd)
{
	write(fd, &ch, 1);
}

/**
 * _strdup - Duplicate a null-terminated string.
 * @s1: The source string to be duplicated.
 * Return: A pointer to the new duplicated string, or NULL on failure.
 */
char	*_strdup(const char *s1)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	len = _strlen(s1);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (*s1)
	{
		dst[i] = *s1;
		i++;
		s1++;
	}
	dst[i] = '\0';
	return (dst);
}

/**
 * check_char - Check if a character exists in a given string.
 * @input: The input string to search for the character.
 * @c: The character to check for.
 * Return: 1 if the character is found in the string, 0 otherwise.
 */
int	check_char(char *input, int c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
