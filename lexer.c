#include "simpleshell.h"

void	ft_builtins(t_env *envr, t_cmd *f_list)
{
	if (f_list && !ft_strcmp(f_list->cmd[0], "cd"))
		change_dir(&envr, f_list);
	if (f_list->cmd && f_list->cmd[0] && !ft_strcmp(f_list->cmd[0], "exit"))
		ft_exit(f_list->cmd, f_list);
	else if (f_list->cmd && f_list->cmd[0] && !ft_strcmp(f_list->cmd[0], "env"))
		env_parsing(f_list->cmd, envr);
}

void	lexer(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
        if (tmp->prev == NULL && ft_strcmp(tmp->content, ">>")
            && ft_strcmp(tmp->content, ">") && ft_strcmp(tmp->content, "<")
            && ft_strcmp(tmp->content, "<<") && tmp->content[0] != '\"'
            && tmp->content[0] != '\'')
            tmp->type = ft_strdup("COMMAND");
        else if (!ft_strcmp(tmp->content, " "))
            tmp->type = ft_strdup("space");
        else if (tmp->content[0] == '-')
            tmp->type = ft_strdup("FLAG");
        else if (tmp->content[0] == '\"')
            tmp->type = ft_strdup("DOUBLE_Q");
        else if (tmp->content[0] == '\'')
            tmp->type = ft_strdup("SINGLE_Q");
        else
            tmp->type = ft_strdup("COMMAND");
		tmp = tmp->link;
	}
}
