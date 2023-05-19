#include "shell.h"
/**
 * get_environ - returns a copy of the string array of environment variables
 * @info: structure containing relevant information
 * Return: Copy of the environment variables array
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unset_env_var - Removes an environment variable
 * @info: Structure containing relevant information
 * @var: The name of the environment variable to remove
 * Return: 1 if variable is deleted, 0 otherwise
 */
int _unset_env_var(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *equal_sign;

	if (!node || !var)
		return (0);
	while (node)
	{
		equal_sign = starts_with(node->str, var);
		if (equal_sign && *equal_sign == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _set_env_var - initializes a new environment variable or
 *	modifies an existing one
 * @info: Structure containing relevant information
 * @var: The name of the environment variable
 * @value: The value of the environment variable
 * Return: Always 0
 */
int _set_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *equal_sign;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (noe)
	{
		equal_sign = starts_with(node->str, var);
		if (equal_sign && *equal_sign == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
