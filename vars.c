#include "shell.h"

/**
 * is_chain - Checks if the line contains a command chaining operator.
 * @info: Pointer to the info_t struct.
 * @line: The input line.
 * @i: Pointer to the current index in the line.
 *
 * Return: 1 if a command chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *line, size_t *i)
{
	size_t j = *i;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;

	if (line[j] == ';' || line[j] == '&' || line[j] == '|')
	{
		info->cmd_buf_type = (line[j] == ';') ? CMD_CHAIN :
			((line[j] == '&') ? CMD_AND : CMD_OR);
		check_chain(info, line, i, j, j);
		return (1);
	}

	return (0);
}

/**
 * check_chain - Checks the command chaining sequence in the line.
 * @info: Pointer to the info_t struct.
 * @line: The input line.
 * @i: Pointer to the current index in the line.
 * @j: The starting index of the command chaining sequence.
 * @k: The current index in the command chaining sequence.
 */
void check_chain(info_t *info, char *line, size_t *i, size_t j, size_t k)
{
	while (line[k] && (line[k] == ';' || line[k] == '&' || line[k] == '|'))
		k++;

	while (line[k] && (line[k] == ' ' || line[k] == '\t'))
		k++;

	if (line[k] && (line[k] != ';' && line[k] != '&' && line[k] != '|'))
	{
		*i = k;
		*info->cmd_buf = _strdup(&line[j]);
	}
	else
		*i = j;
}

/**
 * replace_alias - Replaces alias with the corresponding string in argument.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 if the alias is replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	list_t *tmp = info->alias;
	size_t len __attribute__((unused));

	while (tmp)
	{
		len = _strlen(tmp->str);
		if (_strcmp(tmp->str, info->arg) == 0)
		{
			if (replace_string(&info->arg, tmp->str) == -1)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}

	return (0);
}

/**
 * replace_vars - Replaces variables with their corresponding values;
 * in the argument.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 if the variable is replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	list_t *tmp = info->env;
	size_t len __attribute__((unused));

	while (tmp)
	{
		len = _strlen(tmp->str);
		if (_strcmp(tmp->str, info->arg) == 0)
		{
			if (replace_string(&info->arg, tmp->str) == -1)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}

	return (0);
}

/**
 * replace_string - Replaces a variable or alias with a string;
 * in the given argument.
 * @str: Pointer to the argument string.
 * @var: The variable or alias string.
 *
 * Return: 0 on success, -1 on failure.
 */
int replace_string(char **str, char *var)
{
	char *new_str;
	char *ptr;
	size_t len_var;
	size_t len_str;
	size_t len_diff;

	len_var = _strlen(var);
	len_str = _strlen(*str);
	len_diff = len_str - len_var;

	if (len_diff == 0)
	{
		ptr = strstr(*str, var);
		if (ptr != NULL)
		{
			new_str = _realloc(*str, len_str + len_diff + 1, len_str + 1);
			if (new_str == NULL)
				return (-1);

			ptr = new_str + (ptr - *str);
			_strcpy(ptr + len_var, ptr);
			_strncpy(ptr, var, len_var);

			*str = new_str;
		}
	}

	return (0);
}
