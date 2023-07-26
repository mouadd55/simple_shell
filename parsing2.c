#include "simpleshell.h"

/**
 * syntax_error - Display a syntax error message to the standard error stream.
 * @s2: A string to be included in the error message.
 * @e: A character to be appended to the error message.
 */
void	syntax_error(char *s2, char e)
{
	_printf("Shell: : syntax error near unexpected token ", 2);
	if (s2)
		_printf("%s", 2, s2);
	if (e)
		_putchar(e, 2);
	_putchar('\n', 2);
	return ;
}

/**
 * search_for_pipe - Check if there is a "PIPE" token in the linked list of commands.
 * @v: A pointer to the t_vars structure containing shell variables.
 * Return: 1 if a "PIPE" token is found, 0 otherwise.
 */
int	search_for_pipe(t_vars *v)
{
	while (v->tmp1)
	{
		if (!_strcmp(v->tmp1->type, "PIPE"))
			return (1);
		v->tmp1 = v->tmp1->link;
	}
	return (0);
}

/**
 * _isdigit - Check if a string represents a valid integer.
 * @str: The input string to be checked.
 * Return: 1 if the string represents a valid integer, 0 otherwise.
 */
int	_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (!str[++i])
			return (0);
	while (str[i])
		if (!(str[i] >= '0' && str[i++] <= '9'))
			return (0);
	return (1);
}

