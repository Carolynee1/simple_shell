#include "shell.h"

/**
 * list_len - Calculate the length of a linked list.
 * @head: Pointer to the head of the list.
 *
 * Return: The length of the list.
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * list_to_strings - Convert a linked list to an array of stringd.
 * @head: Pointer to The head of the list.
 *
 * Return: The array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t len = list_len(head);
	char **strings = malloc((len + 1) * sizeof(char *));
	size_t i = 0;
	list_t *current = head;

	if (strings == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	while (current != NULL)
	{
		strings[i] = strdup(current->str);
		if (strings[i] == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		current = current->next;
		i++;
	}
	strings[i] = NULL; /* Add a NULL pointer at end of the array */
	return (strings);
}

/**
 * print_list - Print the contents of a linked list.
 * @head: Pointer to the head of the list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		printf("%s\n", current->str);
		count++;
		current = current->next;
	}

	return (count);
}
/**
 * node_starts_with - Find a node in a linked list based on a string prefix.
 * @head: Pointer to the head of the list.
 * @prefix: Prefix string to search for.
 * @type: Type character ('s' for starts with, 'c' for exact match).
 *
 * Return: Pointer to the found node or NULL if not found.
 */
list_t *node_starts_with(list_t *head, char *prefix, char type)
{
	list_t *current = head;

	while (current != NULL)
	{
	if (type == 's')
		{
	if (starts_with(current->str, prefix))
		return (current);
		}
	else if (type == 'c')
		{
		if (_strcmp(current->str, prefix) == 0)
			return (current);
		}
		current = current->next;
	}

	return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list.
 * @head: pointer to the the head of the list.
 * @node: pointer to the node to find the index of.
 *
 * Return: The index of the node, or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t index = 0;
	list_t *current = head;

	while (current != NULL)
	{
		if (current == node)
			return (index);

		index++;
		current = current->next;
	}

	return (-1); /* Node not found */
}
