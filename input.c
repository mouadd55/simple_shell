#include "simpleshell.h"

/**
 * handle_redirect - Handles redirection symbols '>>' and '<<'
 * in the input string and adds
 *                   them to the linked list of commands accordingly.
 * @lst: A pointer to a pointer to the head of the linked list of commands.
 * @v: A pointer to the t_vars struct containing temporary variables.
 */
void	handle_redirect(t_list **lst, t_vars *v)
{
	if ((v->arr[v->i][v->j] == '>' && v->arr[v->i][v->j + 1] == '>')
		|| (v->arr[v->i][v->j] == '<' && v->arr[v->i][v->j + 1] == '<'))
	{
		_lstadd_back(lst, _lstnew(_substr(&v->arr[v->i][v->j], 0, 2)));
		v->j += 2;
	}
	else
	{
		_lstadd_back(lst, _lstnew(_substr(&v->arr[v->i][v->j], 0, 1)));
		v->j++;
	}
}

/**
 * handle_quotes - Handles quotes (single and double)
 * in the input string and adds the quoted
 *                 substrings to the linked list of commands accordingly.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * @lst: A pointer to a pointer to the head of the linked list of commands.
 * Return: nothing
 * @c: The quote character (single or double).
 */
void	handle_quotes(t_vars *v, t_list **lst, char c)
{
	if (v->arr[v->i][v->j] && !is_special(v->arr[v->i][v->j]))
	{
		if (v->arr[v->i][v->j] && is_quote(v->arr[v->i][v->j]))
		{
			v->start = v->j;
			v->j++;
			while (v->arr[v->i][v->j] && v->arr[v->i][v->j] != c)
				v->j++;
			_lstadd_back(lst, _lstnew(_substr(v->arr[v->i], v->start, v->j
						- v->start + 1)));
			if (v->arr[v->i][v->j])
				v->j++;
		}
		else if (v->arr[v->i][v->j] && !is_quote(v->arr[v->i][v->j]))
		{
			v->start = v->j;
			while (v->arr[v->i][v->j] && !is_quote(v->arr[v->i][v->j])
				&& !is_special(v->arr[v->i][v->j]))
				v->j++;
			_lstadd_back(lst, _lstnew(_substr(v->arr[v->i], v->start, v->j
						- v->start)));
		}
	}
	if (v->arr[v->i][v->j] && is_special(v->arr[v->i][v->j]))
		handle_redirect(lst, v);
}

/**
 * split_input - Splits the input string into individual command tokens and
 *               handles redirection and quotes in the input.
 * @lst: A pointer to a pointer to the head of the linked list of commands.
 * @v: A pointer to the t_vars struct containing temporary variables.
 * Return: nothing
 */
static void	split_input(t_list **lst, t_vars *v)
{
	if (v->arr[v->i] && (check_char(v->arr[v->i], '\"')
			|| check_char(v->arr[v->i], '\'')))
	{
		while (v->arr[v->i][v->j])
			handle_quotes(v, lst, v->arr[v->i][v->j]);
	}
	else
	{
		while (v->arr[v->i][v->j])
		{
			if (v->arr[v->i][v->j] && is_special(v->arr[v->i][v->j]))
				handle_redirect(lst, v);
			else
			{
				v->start = v->j;
				while (v->arr[v->i][v->j] && !is_special(v->arr[v->i][v->j]))
					v->j++;
				v->end = v->j - v->start;
				_lstadd_back(lst, _lstnew(_substr(v->arr[v->i], v->start,
							v->end)));
			}
		}
	}
}

/**
 * _split_input - Splits the input string into individual command tokens and
 *               handles redirection and quotes in the input.
 * @input: The input string to be split.
 * Return: A pointer to the head of the linked list of commands.
 */
t_list	*_split_input(char *input)
{
	t_list	*lst;
	t_vars	v;
	t_list	*tmp;

	v.i = 0;
	v.j = 0;
	lst = NULL;
	switch_space(input, 1);
	v.arr = _split(input, " \t");
	while (v.arr && v.arr[v.i])
	{
		v.j = 0;
		split_input(&lst, &v);
		v.i++;
		if (v.arr[v.i])
			_lstadd_back(&lst, _lstnew(_strdup(" ")));
	}
	_free_arr(v.arr);
	tmp = lst;
	while (tmp)
	{
		switch_space(tmp->content, 0);
		tmp = tmp->link;
	}
	return (lst);
}
