#include "simpleshell.h"

/**
 * _lstnew_env - Create a new node for the t_env linked list.
 * @key: The data to be stored in the new node.
 * @value: The data to be stored in the new node.
 * Return: A pointer to the newly created t_env node, or NULL on failure.
 */
t_env	*_lstnew_env(char *key, char *value)
{
	t_env	*head;

	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->key = key;
	head->value = value;
	head->link = NULL;
	head->prev = NULL;
	return (head);
}

/**
 * _lstlast_env - Find the last node of the t_env linked list.
 * @head: The head of the t_env linked list.
 * Return: A pointer to the last node of the
 * linked list, or NULL if the list is empty.
 */
t_env	*_lstlast_env(t_env *head)
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
 * _lstadd_back_env - Add a new node to the end of the t_env linked list.
 *
 * @head: A pointer to a pointer to the head of the t_env linked list.
 * @new: The new node to be added.
 */
void	_lstadd_back_env(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head || !head)
		*head = new;
	else
	{
		tmp = _lstlast_env(*head);
		tmp->link = new;
		new->prev = tmp;
	}
}

/**
 * _lstsize_env - Calculate the number of nodes
 * (commands) in the t_env linked list.
 * @env: The head of the t_env linked list.
 * Return: The number of nodes (commands) in the linked list.
 */
int	_lstsize_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->link;
	}
	return (count);
}

/**
 * _destroy_list_env - Free the memory allocated for the t_cmd
 * linked list and its commands.
 * @head: A pointer to a pointer to the head of the t_cmd linked list.
 * Return: nothing
 */
void	*_destroy_list_env(t_env **head)
{
	t_env	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		tmp = (*head)->link;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		(*head) = tmp;
	}
	return (0);
}
