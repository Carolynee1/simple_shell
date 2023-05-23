#include "shell.h"

/**
 * _getenv - Retrieves the value of an environment variable
 * @info: Pointer to info_t struct
 * @name: Name of the environment variable
 *
 * Return: Value of the environment variable or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *env = info->env;
	char *value = NULL;

	while (env != NULL)
	{
		if (_strcmp(env->str, name) == 0)
		{
			value = _strchr(env->str, '=') + 1;
			break;
		}
		env = env->next;
	}
	return (value);
}

/**
 *_myenv - Prints the current environment variables
 * @info: Pointer to info_t struct
 *
 * Return: Always0 on success,
 */
int _myenv(info_t *info)
{
	list_t *env = info->env;

	while (env != NULL)
	{
		_puts(env->str);
		_putchar('\n');
		env = env->next;
	}
	return (0);
}

/**
 *_mysetenv - Sets the value of an environment variable
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, 2 on failure
 */
int _mysetenv(info_t *info)
{
	char *name, *value;
	char *env_str;
	char **environ = info->environ;

	if (info->argc != 3)
	{
		print_error(info, "setenv: Incorrect number of arguments");
		return (2);
	}
	name = info->argv[1];
	value = info->argv[2];

	environ str = malloc(_strlen(name) + _strlen(value) + 2);
	if (env_str == NULL)
	{
		print_error(info, "setenv: Memory allocation failed");
		return (2);
	}
	_strcpy(env_str, name);
	_strcat(env_str, "=");
	_strcat(env_str, value);
	
	if (_setenv(info, name, value) == -1)
	{
		if (bfree((void **)&env_str) == -1)
		{
			print_error(info, "setenv: Memory deallocation failed");
			return (2);
		}
		return (2);
	}
	while (*environ != NULL)
	{
		if (_strcmp(*environ, name) == 0)
		{
			if (bfree((void **)environ) == -1)
			{
				print_error(info, "setenv: Memory deallocation failed");
				return (2);
			}
			break;
		}
		environ++;
	}

	*environ = env_str;

	return (0);
}
/**
 * _myunsetenv - Removes an environment variable
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, 2 on failure
 */
int _myunsetenv(info_t *info)
{
	char *name;
	char **environ = info->environ;

	if (info->argc != 2)
	{
		print_error(info, "unsetenv: Incorrect number of arguments");
		return (2);
	}
	name = info->argv[1];

	if (_unsetenv(info, name) == -1)
	{
		return (2);
	}
	while (*environ != NULL)
	{
		if (_strcmp(*environ, name) == 0)
		{
			if (bfree((void **)environ) == -1)
			{
				print_error(info, "unsetenv: Memory deallocation failed");
				return (2);
			}
			break;
		}
		environ++;
	}
	return (0);
}

/**
 * populate_env_list - Populates the env list with current environment variables
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int populate_env_list(info_t *info)
{
	char **environ = environ;
	list_t *env = NULL;
	list_t *temp = NULL;
	int index = 0;

	while (*environ != NULL)
	{
		temp = add_node_end(&env, *environ, index);
		if (temp == NULL)
		{
			free_list(&env);
			print_error(info, "populate_env_list: Memory allocation failed");
			return (-1);
		}
		environ++;
		index++;
	}
	info->env = env;
	return (0);
}
