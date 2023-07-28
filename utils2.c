#include "simpleshell.h"

/**
 * _count_words - Count the number of words in a string, delimited
 * by specific characters.
 * @s: The input string.
 * @c: The set of characters that delimit the words.
 * Return: The number of words in the string.
 */
int	_count_words(char const *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && check_char(c, s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !check_char(c, s[i]))
			i++;
	}
	return (count);
}

void *_re_alloc(void *addr, size_t before, size_t after)
{
	char *buf;
    char *str;
	unsigned int a;

    a = 0;
	if (after == before)
		return (addr);
	if (!addr)
	{
		buf = malloc(after);
		if (!buf)
			return (0);
		return (buf);
	}
	if (!after && addr)
	{
		free(addr);
		return (0);
	}
	buf = malloc(after);
	if (!buf)
		return (0);
	str = addr;
	while (a < before)
    {
		buf[a] = str[a];
        a++;
    }
	free(addr);
	return (buf);
}

/**
 * _lenword - Calculate the length of a word in a string, delimited
 * by specific characters.
 * @s: The input string.
 * @c: The set of characters that delimit the words.
 * Return: The length of the word.
 */
static int	_lenword(char const *s, char *c)
{
	int	i;

	i = 0;
	while (s[i] && !check_char(c, s[i]))
		i++;
	return (i);
}

/**
 * _free_arr - Free a dynamically allocated array of strings and its contents.
 * @str: The array of strings to be freed.
 * Return: Always returns NULL (0).
 */
char	**_free_arr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

/**
 * _split - Split a string into an array of substrings, using
 * specified delimiters.
 * @s: The input string to be split.
 * @c: The set of characters that delimit the substrings.
 * Return: A newly allocated array of strings containing the substrings,
 *         or NULL on failure.
 */
char	**_split(char const *s, char *c)
{
	int		i;
	char	**str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((_count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (*s)
	{
		while (check_char(c, *s))
			s++;
		if (*s)
		{
			str[i] = _substr(s, 0, _lenword(s, c));
			if (!str[i])
				return (_free_arr(str));
			i++;
		}
		while (!check_char(c, *s) && *s)
			s++;
	}
	str[i] = 0;
	return (str);
}
