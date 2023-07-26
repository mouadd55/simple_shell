#include "simpleshell.h"

/**
 * spaces_in_quotes_utils - Utility function to handle spaces within quotes.
 * @str: The input string to be processed.
 * @idx: An integer flag (1 for setting spaces to negative, 0 for
 * setting negative spaces to positive).
 * Return: A new string with spaces handled accordingly, or NULL on failure.
 */
char	*spaces_in_quotes_utils(char *str, int idx)
{
	int		i;
	char	*updated_str;

	i = 0;
	if (!str)
		return (0);
	updated_str = malloc(sizeof(char) * (_strlen(str) + 1));
	if (!updated_str)
		return (0);
	while (str[i])
	{
		if (is_space(str[i]) && idx == 1)
			updated_str[i] = str[i] * (-1);
		else if (str[i] < 0 && idx == 0)
			updated_str[i] = str[i] * (-1);
		else
			updated_str[i] = str[i];
		i++;
	}
	updated_str[i] = '\0';
	if (idx == 0)
		free(str);
	return (updated_str);
}

/**
 * spaces_in_quotes - Updates the command list by
 * handling spaces within quotes.
 * @final_list: A pointer to a pointer to the head of the command list.
 */
void	spaces_in_quotes(t_cmd **final_list)
{
	int		i;
	t_cmd	*tmp;

	tmp = *final_list;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd && tmp->cmd[++i])
			tmp->cmd[i] = spaces_in_quotes_utils(tmp->cmd[i], 0);
		tmp = tmp->link;
	}
}

/**
 * create_string_for_each_cmd - Creates a string representation
 * for each command in the input list.
 * @list: A pointer to the current node in the input list.
 * @v: A pointer to the t_vars struct containing temporary variables.
 */
void	create_string_for_each_cmd(t_list *list, t_vars *v)
{
	if (list->type[0] == 'S' || !_strcmp(list->type, "DOUBLE_Q"))
	{
		v->tmp = spaces_in_quotes_utils(list->content, 1);
		v->str = _strjoin(v->str, v->tmp);
		free(v->tmp);
		v->tmp = NULL;
	}
	if (list->type[0] == 'C' || !_strcmp(list->type, "FLAG"))
		v->str = _strjoin(v->str, list->content);
	else if (list->type[0] == 's')
		v->str = _strjoin(v->str, " ");
}

/**
 * create_final_list - Creates the final list of commands
 * by combining command strings
 *                     separated by pipes from the input list.
 * @list: A pointer to the head of the input list.
 * @final_list: A pointer to a pointer to the head of
 * the final list of commands.
 */
void	create_final_list(t_list *list, t_cmd **final_list)
{
	t_vars	v;

	v.tmp = NULL;
	v.str = NULL;
	while (list)
	{
		while (list && _strcmp(list->type, "PIPE"))
		{
			create_string_for_each_cmd(list, &v);
			list = list->link;
		}
		lstadd_back_final(final_list, lstnew_final(_split(v.str, " ")));
		free(v.str);
		v.str = NULL;
		if (list)
			list = list->link;
	}
	spaces_in_quotes(final_list);
}
