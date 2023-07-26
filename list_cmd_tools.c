#include "simpleshell.h"

/**
 * lstnew_final - Create a new node for the t_cmd linked list.
 * @command: The command to be stored in the new node.
 * Return: A pointer to the newly created t_cmd node, or NULL on failure.
 */
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

/**
 * lstlast_final - Find the last node of the t_cmd linked list.
 * @head: The head of the t_cmd linked list.
 * Return: A pointer to the last node of the linked list, or
 * NULL if the list is empty.
 */
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

/**
 * lstadd_back_final - Add a new node to the end of the t_cmd linked list.
 *
 * @head: A pointer to a pointer to the head of the t_cmd linked list.
 * @new: The new node to be added.
 */
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

/**
 * lstsize_cmd - Calculate the number of nodes
 * (commands) in the t_cmd linked list.
 * @lst: The head of the t_cmd linked list.
 * Return: The number of nodes (commands) in the linked list.
 */
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


/**
 * _destroy_final - Free the memory allocated for
 * the t_cmd linked list and its commands.
 * @head: A pointer to a pointer to the head of the t_cmd linked list.
 * Return: nothing
 */
void	*_destroy_final(t_cmd **head)
{
	t_cmd	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		tmp = (*head)->link;
		if ((*head)->cmd)
			_free_arr((*head)->cmd);
		free(*head);
		(*head) = tmp;
	}
	return (0);
}
