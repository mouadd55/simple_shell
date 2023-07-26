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

void	more_lexer_conditions(t_list *tmp)
{
	if (!ft_strcmp(tmp->content, "|"))
		tmp->type = ft_strdup("PIPE");
	else if (!ft_strcmp(tmp->content, " "))
		tmp->type = ft_strdup("space");
	else if (tmp->content[0] == '-')
		tmp->type = ft_strdup("FLAG");
	else if (tmp->content[0] == '\"')
		tmp->type = ft_strdup("DOUBLE_Q");
	else if (tmp->content[0] == '\'')
		tmp->type = ft_strdup("SINGLE_Q");
	else if (!ft_strcmp(tmp->content, "<<"))
		tmp->type = ft_strdup("HEREDOC");
	else if (!ft_strcmp(tmp->content, ">>"))
		tmp->type = ft_strdup("APPEND");
	else if (!ft_strcmp(tmp->content, ">"))
		tmp->type = ft_strdup("OUTFILE");
	else if (!ft_strcmp(tmp->content, "<"))
		tmp->type = ft_strdup("INFILE");
}

void	moooore_conditions(t_list *tmp)
{
	if (tmp->prev && !tmp->prev->prev && (!ft_strcmp(tmp->prev->content, "<")
			|| !ft_strcmp(tmp->prev->content, ">")
			|| !ft_strcmp(tmp->prev->content, ">>")))
		tmp->type = ft_strdup("FILE");
	else
		tmp->type = ft_strdup("COMMAND");
}

void	first_conditions(t_list *tmp)
{
	if (tmp->prev == NULL && ft_strcmp(tmp->content, ">>")
		&& ft_strcmp(tmp->content, ">") && ft_strcmp(tmp->content, "<")
		&& ft_strcmp(tmp->content, "<<") && tmp->content[0] != '\"'
		&& tmp->content[0] != '\'')
		tmp->type = ft_strdup("COMMAND");
	else if (!ft_strcmp(tmp->content, "|") || !ft_strcmp(tmp->content, " ")
		|| tmp->content[0] == '-' || tmp->content[0] == '\"'
		|| tmp->content[0] == '\'' || !ft_strcmp(tmp->content, "<<")
		|| !ft_strcmp(tmp->content, ">>") || !ft_strcmp(tmp->content,
			">") || !ft_strcmp(tmp->content, "<"))
		more_lexer_conditions(tmp);
	else if ((tmp->prev && tmp->prev->prev
			&& (!ft_strcmp(tmp->prev->content, "<<")
				|| !ft_strcmp(tmp->prev->prev->content, "<<")))
		|| (tmp->prev && !ft_strcmp(tmp->prev->content, "<<")))
		tmp->type = ft_strdup("DELIMITER");
	else
		moooore_conditions(tmp);
}

void	lexer(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		first_conditions(tmp);
		tmp = tmp->link;
	}
}
