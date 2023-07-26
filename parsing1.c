#include "simpleshell.h"

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

/**
 * ft_count_char - Count the occurrences of a character in a string.
 * @input: The input string to count the occurrences in.
 * @c: The character to count.
 * Return: The number of occurrences of the character in the string.
 */
size_t	ft_count_char(char *input, char c)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (input[i] == c)
			count++;
	}
	return (count);
}

/**
 * check_syntax2 - Check for specific syntax errors in the linked list of commands.
 * @lst: A pointer to the head of the linked list of commands.
 * Return: 258 if a syntax error is found, 0 otherwise.
 */
int	check_syntax2(t_list *lst)
{
	if ((lst->content[0] == '|' && lst->link->content[0] == '|')
		|| (lst->content[0] == '|' && lst->link->content[0] == 32
			&& lst->link->link->content[0] == '|'))
		return (syntax_error(NULL, '|'), 258);
	else if (check_char(lst->content, '(') || check_char(lst->content, ')'))
		return (syntax_error(lst->content, 0), 258);
	else if (lst->content[0] == '\'' && (lst->content[ft_strlen(lst->content)
				- 1] != '\'' || !lst->content[1]))
		return (syntax_error(NULL, lst->content[0]), 258);
	else if (lst->content[0] == '\"' && (lst->content[ft_strlen(lst->content)
				- 1] != '\"' || !lst->content[1]))
		return (syntax_error(NULL, lst->content[0]), 258);
	else if ((!ft_strcmp(lst->content, ">>") && lst->link->content[0] == '|')
		|| (!ft_strcmp(lst->content, ">>") && lst->link->content[0] == 32
			&& lst->link->link->content[0] == '|'))
		return (syntax_error(NULL, '|'), 258);
	else if ((!ft_strcmp(lst->content, ">") && lst->link->content[0] == '|'))
		return (syntax_error(NULL, '|'), 258);
	return (0);
}

/**
 * check_syntax - Check for general syntax errors in the linked list of commands.
 * @lst: A pointer to the head of the linked list of commands.
 * Return: 258 if a syntax error is found, 0 otherwise.
 */
int	check_syntax(t_list *lst)
{
	while (lst)
	{
		if ((ft_lstsize(lst) == 1 && check_char("><|", lst->content[0]))
			|| check_char("><|", ft_lstlast(lst)->content[0]))
			return (syntax_error("`newline'", 0), 258);
		else if ((check_char("><", lst->content[0])) && check_char("><",
				lst->link->content[0]))
			return (syntax_error(NULL, lst->link->content[0]), 258);
		else if ((check_char("><", lst->content[0])
				&& lst->link->content[0] == 32) && check_char("><",
				lst->link->link->content[0]))
			return (syntax_error(lst->link->link->content, 0), 258);
		else if (lst->content[0] == '>' && lst->link->content[0] == 32
			&& lst->link->link->content[0] == '|')
			return (syntax_error(lst->link->link->content, 0), 258);
		else if (check_syntax2(lst))
			return (258);
		lst = lst->link;
	}
	return (0);
}

/**
 * ft_atoi - Convert a string to a long long integer.
 * @str: The input string to convert.
 * Return: The converted long long integer.
 */
long long	ft_atoi(const char *str)
{
	long long	i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}
