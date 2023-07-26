#include "simpleshell.h"

void	_builtins(t_env *envr, t_cmd *f_list)
{
	if (f_list && !_strcmp(f_list->cmd[0], "cd"))
		change_dir(&envr, f_list);
	if (f_list->cmd && f_list->cmd[0] && !_strcmp(f_list->cmd[0], "exit"))
		ft_exit(f_list->cmd, f_list);
	else if (f_list->cmd && f_list->cmd[0] && !_strcmp(f_list->cmd[0], "env"))
		env_parsing(f_list->cmd, envr);
}

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
