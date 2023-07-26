#include "simpleshell.h"

/**
 * _builtins - Checks if the given command is a built-in
 * command (cd, exit, or env)
 * and performs the corresponding action if it matches.
 * @envr: A pointer to the environment variable linked list.
 * @f_list: A pointer to the command linked list node to be checked.
 * Return: None. Modifies the program state based on the built-in command.
 */
void	_builtins(t_env *envr, t_cmd *f_list)
{
	if (f_list && !_strcmp(f_list->cmd[0], "cd"))
		change_dir(&envr, f_list);
	if (f_list->cmd && f_list->cmd[0] && !_strcmp(f_list->cmd[0], "exit"))
		ft_exit(f_list->cmd, f_list);
	else if (f_list->cmd && f_list->cmd[0] && !_strcmp(f_list->cmd[0], "env"))
		env_parsing(f_list->cmd, envr);
}

/**
 * lexer - Performs lexical analysis on the linked list of commands,
 * setting the type of each node.
 * @list: A pointer to a pointer to the head of the linked list of commands.
 * Return: None. Modifies the type field of the nodes in the linked list.
 */
void	lexer(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->prev == NULL && _strcmp(tmp->content, ">>")
			&& _strcmp(tmp->content, ">") && _strcmp(tmp->content, "<")
			&& _strcmp(tmp->content, "<<") && tmp->content[0] != '\"'
			&& tmp->content[0] != '\'')
			tmp->type = _strdup("COMMAND");
	else if (!_strcmp(tmp->content, " "))
		tmp->type = _strdup("space");
	else if (tmp->content[0] == '-')
		tmp->type = _strdup("FLAG");
	else if (tmp->content[0] == '\"')
		tmp->type = _strdup("DOUBLE_Q");
	else if (tmp->content[0] == '\'')
		tmp->type = _strdup("SINGLE_Q");
	else
		tmp->type = _strdup("COMMAND");
	tmp = tmp->link;
	}
}

/**
 * _getenv - Get the value of an environment variable.
 * @env: A pointer to the environment list.
 * @key: The key of the environment variable to retrieve.
 * Return: The value of the environment variable if found, otherwise NULL.
 */
char	*_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (!_strcmp(env->key, key))
			return (env->value);
		env = env->link;
	}
	return (NULL);
}
