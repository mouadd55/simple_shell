#include "simpleshell.h"

void	switch_space(char *input, int x)
{
	t_vars	v;

	v.i = 0;
	while (input[v.i] && x)
	{
		if (input[v.i] == '\'' && ft_strchr(&input[v.i + 1], '\''))
		{
			while (input[++v.i] && input[v.i] != '\'')
				if (is_space(input[v.i]))
					input[v.i] *= -1;
		}
		else if (input[v.i] == '\"' && ft_strchr(&input[v.i + 1], '\"'))
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

char	is_quote(char input)
{
	if (input == '\"' || input == '\'')
		return (input);
	return (0);
}

char	is_special(char c)
{
	if (check_char("()=+|><$?", c))
		return (c);
	return (0);
}
