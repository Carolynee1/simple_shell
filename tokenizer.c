#include "shell.h"

/**
 * strtow - Splits a string into an array of strings using a delimiter string.
 * @str: The input string to split.
 * @delimiter: The delimiter string.
 *
 * Return: An array of strings (char **) or NULL on failure.
 */
char **strtow(char *str, char *delimiter)
{
	char **result = NULL;
	char *token;
	int count = 0;
	int i;

	token = strtok(str, delimiter);

	while (token != NULL)
	{
		result = realloc(result, (count + 1) * sizeof(char *));
		result[count] = token;
		count++;
		token = strtok(NULL, delimiter);
	}

	result = realloc(result, (count + 1) * sizeof(char *));
	result[count] = NULL;

	return (result);
}

/**
 * strtow2 - Splits a string into an array of strings,
 * using a single character delimiter.
 * @str: The input string to split.
 * @delimiter: The delimiter character.
 *
 * Return: An array of strings (char **) or NULL on failure.
 */
char **strtow2(char *str, char delimiter)
{
	char **result = NULL;
	char *token;
	int count = 0;
	int i;

	token = strtok(str, &delimiter);

	while (token != NULL)
	{
		result = realloc(result, (count + 1) * sizeof(char *));
		result[count] = token;
		count++;
		token = strtok(NULL, &delimiter);
	}

	result = realloc(result, (count + 1) * sizeof(char *));
	result[count] = NULL;

	return (result);
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0.
 */

int main(void)
{
	char str1[] = "Hello World, How are you?";
	char str2[] = "Welcome,to,the,world";
	char delimiter1[] = " ";
	char delimiter2 = ',';
	char **result1, **result2;
	int i;

	result1 = strtow(str1, delimiter1);
	if (result1 != NULL)
	{
		printf("Result1:\n");
		for (i = 0; result1[i] != NULL; i++)
		{
			printf("%s\n", result1[i]);
		}
		free(result1);
	}

	result2 = strtow2(str2, delimiter2);
	if (result2 != NULL)
	{
		printf("Result2:\n");
		for (i = 0; result2[i] != NULL; i++)
		{
			printf("%s\n", result2[i]);
		}
		free(result2);
	}

	return (0);
}

