#include "simpleshell.h"

/**
 * _lstnew - Create a new node for the t_list linked list.
 * @content: The data to be stored in the new node.
 * Return: A pointer to the newly created t_list node, or NULL on failure.
 */
t_list	*_lstnew(char *content)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->type = NULL;
	head->link = NULL;
	head->prev = NULL;
	return (head);
}

/**
 * _lstlast - Find the last node of the t_list linked list.
 * @head: The head of the t_list linked list.
 * Return: A pointer to the last node of the linked list, or
 * NULL if the list is empty.
 */
t_list	*_lstlast(t_list *head)
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
 * _lstadd_back - Add a new node to the end of the t_list linked list.
 *
 * @head: A pointer to a pointer to the head of the t_list linked list.
 * @new: The new node to be added.
 */
void	_lstadd_back(t_list **head, t_list *new)
{
	t_list	*tmp;

	if (!*head || !head)
		*head = new;
	else
	{
		tmp = _lstlast(*head);
		tmp->link = new;
		new->prev = tmp;
	}
}

/**
 * _destroy_list - Free the memory allocated for the t_list
 * linked list and its commands.
 * @head: A pointer to a pointer to the head of the t_list linked list.
 * Return: nothing
 */
void	*_destroy_list(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		tmp = (*head)->link;
		free((*head)->content);
		if ((*head)->type)
			free((*head)->type);
		free(*head);
		(*head) = tmp;
	}
	head = NULL;
	return (0);
}

/**
 * _lstsize - Calculate the number of nodes (commands)
 * in the t_list linked list.
 * @lst: The head of the t_list linked list.
 * Return: The number of nodes (commands) in the linked list.
 */
int	_lstsize(t_list *lst)
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
