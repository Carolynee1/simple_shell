#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The number of characters to be copied
 *
 * Return: A pointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
/**
 * _strncat - Concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of characters to be used
 *
 * Return: A pointer to the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[dest_len + i] = src[i];

	if (i < n)
		dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 *
 * Return: A pointer to the first occurrence of the character,
 *	or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}
