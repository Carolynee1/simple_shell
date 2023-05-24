#include "shell.h"


/**
 * _strlen - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *str)
{
	int length = 0;

	while (str[length] != '\0')
		length++;

	return (length);
}

/**
 * _strcmp - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if the strings are equal, otherwise the difference
 * between the ASCII values of the first differing characters.
 */
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0')
			return (0);
		i++;
	}

	return (str1[i] - str2[i]);
}

/**
 * starts_with - Checks if a string starts with a specific prefix.
 * @str: The string to check.
 * @prefix: The prefix to search for.
 *
 * Return: A pointer to the remaining string if the prefix is found,
 * otherwise NULL.
 */
char *starts_with(const char *str, const char *prefix)
{
	while (*prefix != '\0')
	{
		if (*str != *prefix)
			return (NULL);
		str++;
		prefix++;
	}
	return (str);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the resulting string.
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*ptr != '\0')
		ptr++;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
