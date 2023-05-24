#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The input string.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	char *duplicate = NULL;
	int length = 0;
	int i;

	while (str[length] != '\0')
		length++;

	duplicate = (char *)malloc((length + 1) * sizeof(char));

	if (duplicate == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
		duplicate[i] = str[i];

	return (duplicate);
}

/**
 * _puts - Prints a string.
 * @str: The input string.
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to be written.
 *
 * Return: On success, returns the character written.
 * On error, returns EOF.
 */
int _putchar(char c)
{
	char source[] = "Hello, World!";
	char destination[20];
	char *duplicate = NULL;
	_strcpy(destination, source);
	_puts(destination);

	  duplicate = _strdup(source);

	if (duplicate != NULL)
	{
		_puts(duplicate);
		free(duplicate);
	}

	_putchar('\n');

	return (0);
	return (putchar(c));
}
