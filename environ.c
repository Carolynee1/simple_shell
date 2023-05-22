#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _getenv - Get value of an environment variable
 * @info: Pointer to info_t struct
 * @name: Name of the environment variable
 *
 * Return: Pointer to the value of the environment variable
 */
char *_getenv(info_t *info, const char *name)
{
	/* Code to get value of an environment variable */

	return (getenv(name));
}

/**
 *_myenv - Display all environment variables
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int _myenv(info_t *info)
{
	char **env = info->environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}

	return (0); /* or -1 on failure */
}

/**
 *_mysetenv - Set the value of an environment variable
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int _mysetenv(info_t *info)
{
	/* Code to set the value of an environment variable */

	return (setenv(name, value, overwrite));
}

/**
 * _myunsetenv - Unset an environment variable
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int _myunsetenv(info_t *info)
{
	/* Code to unset an environment variable */

	return (unsetenv(name));
}

/**
 * populate_env_list - Populate the environment variable list
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int populate_env_list(info_t *info)
{
	char **env = info->environ;

	while (*env != NULL)
	{
		/* Code to populate the environment variable list */

		env++;
	}

	return (0); /* or -1 on failure */
}
