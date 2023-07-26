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
	write (fd, &ch, 1);
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
 * _strjoin - Concatenate two null-terminated strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: A newly allocated pointer to the concatenated string, or NULL on failure.
 */
char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = _strdup("");
	if (!s2)
		return (NULL);
	str = malloc((_strlen(s1) + _strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
