#include "simpleshell.h"


/**
 * ft_count_words - Count the number of words in a string, delimited by specific characters.
 * @s: The input string.
 * @c: The set of characters that delimit the words.
 * Return: The number of words in the string.
 */
int	ft_count_words(char const *s, char *c)
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

/**
 * ft_lenword - Calculate the length of a word in a string, delimited by specific characters.
 * @s: The input string.
 * @c: The set of characters that delimit the words.
 * Return: The length of the word.
 */
static int	ft_lenword(char const *s, char *c)
{
	int	i;

	i = 0;
	while (s[i] && !check_char(c, s[i]))
		i++;
	return (i);
}

/**
 * ft_free_arr - Free a dynamically allocated array of strings and its contents.
 * @str: The array of strings to be freed.
 * Return: Always returns NULL (0).
 */
char	**ft_free_arr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	return (0);
}

/**
 * ft_split - Split a string into an array of substrings, using specified delimiters.
 * @s: The input string to be split.
 * @c: The set of characters that delimit the substrings.
 * Return: A newly allocated array of strings containing the substrings,
 *         or NULL on failure.
 */
char	**ft_split(char const *s, char *c)
{
	int		i;
	char	**str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (*s)
	{
		while (check_char(c, *s))
			s++;
		if (*s)
		{
			str[i] = ft_substr(s, 0, ft_lenword(s, c));
			if (!str[i])
				return (ft_free_arr(str));
			i++;
		}
		while (!check_char(c, *s) && *s)
			s++;
	}
	str[i] = 0;
	return (str);
}
