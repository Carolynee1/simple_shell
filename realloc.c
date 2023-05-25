#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: byte to fill *s with
 * @n: amount of bytes to be filled
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @arr: string of strings
 */
void ffree(char **arr)
{
	char **a = arr;

	if (!arr)
		return;

	while (*arr)
	{
		free(*arr);
		arr++;
	}

	free(a);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: Pointer to the previous memory block
 * @old_size: size of the previou memory block
 * @new_size: size of the new memory block
 *
 * Return: pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size > old_size)
		_memset(new_ptr + old_size, '\0', new_size - old_size);

	while (old_size > 0)
	{
		old_size--;
		new_ptr[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	}
	return (new_ptr);
}
