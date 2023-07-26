#include "simpleshell.h"

/**
 * ft_strlen - Calculate the length of a null-terminated string.
 * @str: A pointer to the null-terminated string.
 * Return: The length of the string (excluding the null terminator).
 */
size_t	ft_strlen(const char *str)
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
 * ft_putchar - Write a character to a file descriptor.
 * @ch: The character to be written.
 * @fd: The file descriptor where the character will be written.
 */
void	ft_putchar(char ch, int fd)
{
	write (fd, &ch, 1);
}

/**
 * ft_strdup - Duplicate a null-terminated string.
 * @s1: The source string to be duplicated.
 * Return: A pointer to the new duplicated string, or NULL on failure.
 */
char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	len = ft_strlen(s1);
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
 * ft_strjoin - Concatenate two null-terminated strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: A newly allocated pointer to the concatenated string, or NULL on failure.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
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
