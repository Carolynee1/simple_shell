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
