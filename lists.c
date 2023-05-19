#include "shell.h"

/**
 * add_node - Add a new node at the beginning of a linked list.
 * @head: Pointer to the head of the linked list.
 * @str: THe string to be stored in the new node.
 * @num: The number to be stored in the new node.
 *
 * Return: Then address of the newly added node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *temp;

	if (head == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->num = num;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;

	return (new_node);
}
/**
 * add_node_end - add a new node at the end of a linked list.
 * @head: Pointer to the head of the linked list.
 * @str: the string to be stored in the new node.
 * @num: The number to be stored in the new node.
 *
 * Return: The addres of the newly added node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *temp;

	if (head == NULL)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	if (new_node == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->num = num;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;

	return (new_node);
}

/**
 * print_list_str - print the strings in a linked list.
 * @h: Pointer to the head of the linked list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		printf("%s\n", h->str);
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - Delete a node at a given index in a linked list.
 * @head: Pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 *
 * Return: 1 on success, -1 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current, *prev;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;
	prev = NULL;

	while (current != NULL)
	{
		if (i == index)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;

			free(current->str);
			free(current);
			return (1);
		}

		prev = current;
		current = current->next;
		i++;
	}
	return (-1);
}

/**
 * free_list - Free a linked list and its contents.
 * @head: pointer to the head of the linked list.
 */
void free_list(list_t **head)
{
	list_t *current, *next;

	if (head == NULL || *head == NULL)
		return;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}

	*head = NULL;
}
