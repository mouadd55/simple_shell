#include "simpleshell.h"

t_cmd	*lstnew_final(char **command)
{
	t_cmd	*head;

	head = (t_cmd *)malloc(sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->cmd = command;
	head->link = NULL;
	head->prev = NULL;
	return (head);
}

t_cmd	*lstlast_final(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->link == NULL)
			return (head);
		head = head->link;
	}
	return (NULL);
}

void	lstadd_back_final(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head || !head)
		*head = new;
	else
	{
		tmp = lstlast_final(*head);
		tmp->link = new;
		new->prev = tmp;
	}
}

int	lstsize_cmd(t_cmd *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst->link;
	}
	return (counter);
}

void	*ft_destroy_final(t_cmd **head)
{
	t_cmd	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		tmp = (*head)->link;
		if ((*head)->cmd)
			ft_free_arr((*head)->cmd);
		free(*head);
		(*head) = tmp;
	}
	return (0);
}
