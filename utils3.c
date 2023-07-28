#include "simpleshell.h"

/**
 * _strcmp - Compare two null-terminated strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: An integer greater than, equal to, or less than 0, according to
 *         whether s1 is greater than, equal to, or less than s2, respectively.
 */
int	_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _isalpha - Check if a character is an alphabetic character (a-z or A-Z).
 * @ch: The character to be checked.
 * Return: 1 if the character is an alphabetic character, 0 otherwise.
 */
int	_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		return (1);
	return (0);
}

/**
 * _substr - Extract a substring from a given string.
 * @s: The original string.
 * @start: The starting index of the substring.
 * @len: The maximum length of the substring to be extracted.
 * Return: A pointer to the newly allocated substring, or NULL on failure.
 */
char	*_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	if (len == 0 || (start >= _strlen(s)))
		return (_strdup(""));
	if (_strlen(s) < len)
		len = _strlen(s);
	if (_strlen(s + start) < len)
		len = _strlen(s + start);
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (j < _strlen(s) && i < len)
		dest[i++] = s[j++];
	dest[len] = '\0';
	return (dest);
}

/**
 * _strcpy - copy the string pointed to by src to dest
 * @dest: the new copy of src
 * @src: string to copy from
 * Return: the new copy of src
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
