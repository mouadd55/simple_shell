#include "simpleshell.h"

/**
 * ft_strcmp - Compare two null-terminated strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: An integer greater than, equal to, or less than 0, according to
 *         whether s1 is greater than, equal to, or less than s2, respectively.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * ft_isalpha - Check if a character is an alphabetic character (a-z or A-Z).
 * @ch: The character to be checked.
 * Return: 1 if the character is an alphabetic character, 0 otherwise.
 */
int	ft_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		return (1);
	return (0);
}

/**
 * ft_substr - Extract a substring from a given string.
 * @s: The original string.
 * @start: The starting index of the substring.
 * @len: The maximum length of the substring to be extracted.
 * Return: A pointer to the newly allocated substring, or NULL on failure.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	if (len == 0 || (start >= ft_strlen(s)))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (j < ft_strlen(s) && i < len)
		dest[i++] = s[j++];
	dest[len] = '\0';
	return (dest);
}

/**
 * ft_strchr - Locate the first occurrence of a character in a string.
 * @str: The string to search within.
 * @find: The character to find.
 * Return: The index of the first occurrence of the character in the string,
 *         or 0 if the character is not found.
 */
int	ft_strchr(char *str, int find)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) find)
			return (i);
		i++;
	}
	return (0);
}

/**
 * ft_strrchr - Locate the last occurrence of a character in a string.
 * @str: The string to search within.
 * @c: The character to find.
 * Return: The index of the last occurrence of the character in the string,
 *         or 0 if the character is not found.
 */
int	ft_strrchr(char *str, int c)
{
	int	srcl;

	srcl = ft_strlen(str);
	while (srcl >= 0)
	{
		if (str[srcl] == (char) c)
			return (srcl);
		srcl--;
	}
	return (0);
}
