#include "shell.h"

/**
 * bfree - Frees a dynamically allocated memory block
 * @ptr: Pointer to the memory block to be freed
 *
 * Return: 1 if the memory was freed successfully, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

#include "shell.h"
#include <stdlib.h>

/**
 * delete_node - Deletes a node from a linked list.
 * @head: Double pointer to the head of the list.
 * @node: Pointer to the node to be deleted.
 * Return: 1 if deletion is successful, 0 otherwise.
 **/
int delete_node(list_t **head, list_t *node)
{
	list_t *current, *prev;

	if (*head == NULL || node == NULL)
		return (0);

	if (*head == node)
	{
		*head = node->next;
		free(node->str);
		free(node);
		return (1);
	}

	current = *head;
	prev = NULL;

	while (current != NULL && current != node)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL)
		return (0);

	prev->next = current->next;
	free(current->str);
	free(current);

	return (1);
}
