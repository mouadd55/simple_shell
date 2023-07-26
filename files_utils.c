#include "simpleshell.h"

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

int	is_alpha_num(char c)
{
	if (_isalpha(c) || check_char("0123456789", c))
		return (1);
	return (0);
}

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	split_string(t_vars *v, t_cmd *final_list, t_env **envr, int size)
{
	v->tmp1 = _split_input(v->str);
	lexer(&v->tmp1);
	if (size == 1)
		check_cmd(envr, final_list);
	_destroy_list(&v->tmp1);
	free(v->str);
	v->str = NULL;
}
