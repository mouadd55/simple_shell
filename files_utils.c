#include "simpleshell.h"

/**
 * switch_space - Switches spaces within quotes to negative values.
 * When x is 1, it switches spaces to negative values inside quotes.
 * When x is 0, it switches negative values back to positive outside quotes.
 * @input: The input string to be processed.
 * @x: An integer flag (1 for switching spaces to negative,
 * 0 for switching negative spaces to positive).
 */
void	switch_space(char *input, int x)
{
	t_vars	v;

	v.i = 0;
	while (input[v.i] && x)
	{
		if (input[v.i] == '\'' && _strchr(&input[v.i + 1], '\''))
		{
			while (input[++v.i] && input[v.i] != '\'')
				if (is_space(input[v.i]))
					input[v.i] *= -1;
		}
		else if (input[v.i] == '\"' && _strchr(&input[v.i + 1], '\"'))
		{
			while (input[++v.i] && input[v.i] != '\"')
				if (is_space(input[v.i]))
					input[v.i] *= -1;
		}
		v.i++;
	}
	while (input[v.i] && !x)
	{
		if (input[v.i] < 0)
			input[v.i] *= -1;
		v.i++;
	}
}

/**
 * is_quote - Checks if a character is a single quote or double quote.
 * @input: The character to be checked.
 * Return: The character itself if it is a quote, or 0 if it is not.
 */
char	is_quote(char input)
{
	if (input == '\"' || input == '\'')
		return (input);
	return (0);
}

/**
 * is_special - Checks if a character is a special shell character.
 * @c: The character to be checked.
 * Return: The character itself if it is a special shell character,
 * or 0 if it is not.
 */
char	is_special(char c)
{
	if (check_char("()=+|><$?", c))
		return (c);
	return (0);
}

/**
 * is_alpha_num - Checks if a character is an alphabet letter or a digit.
 * @c: The character to be checked.
 * Return: 1 if the character is an alphabet letter or a digit, 0 otherwise.
 */
int	is_alpha_num(char c)
{
	if (_isalpha(c) || check_char("0123456789", c))
		return (1);
	return (0);
}

/**
 * is_space - Checks if a character is a space character
 * (including tabs and spaces).
 * @c: The character to be checked.
 * Return: 1 if the character is a space character, 0 otherwise.
 */
int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
