#include "shell.h"


/**
 * get_history_file - Get history file path
 * @info: Pointer to info_t struct
 *
 * Return: Pointer to history file path, or NULL on failure
 */
char *get_history_file(info_t *info)
{
	char *home;
	char *file_path;
	struct stat st;
	
	home = _getenv(info, "HOME");
	if (home == NULL)
		return (NULL);
	file_path = malloc(sizeof(char) * (strlen(home) + strlen(HIST_FILE) + 2));
	if (file_path == NULL)
		return (NULL);
	strcpy(file_path, home);
	strcat(file_path, "/");
	strcat(file_path, HIST_FILE);
	
	if (stat(file_path, &st) == -1)
	{
		if (errno == ENOENT)
		{
			FILE *file = fopen(file_path, "w");
			if (file == NULL)
			{
				free(file_path);
				return (NULL);
			}
			fclose(file);
		}
		else
		{
			free(file_path);
			return (NULL);
		}
	}
	return (file_path);
}

/**
 * write_history - Write history to a file
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int write_history(info_t *info)
{
	FILE *file;
	list_t *temp;

	file = fopen(get_history_file(info), "w");
	if (file == NULL)
		return (-1);

	temp = info->history;
	while (temp != NULL)
	{
		fprintf(file, "%s\n", temp->str);
		temp = temp->next;
	}
	fclose(file);
	return (0);
}
/**
 * read_history - Read history from a file
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int read_history(info_t *info)
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int linecount = 0;

	file = fopen(get_history_file(info), "r");
	if (file == NULL)
		return (-1);

	while ((read = getline(&line, &len, file)) != -1)
	{
		linecount++;
		if (build_history_list(info, line, linecount) == -1)
		{
			fclose(file);
			free(line);
		}
		return (-1);
	}
	fclose(file);
	free(line);
	return (0);
}

/**
 * build_history_list - Build history linked list
 * @info: Pointer to info_t struct
 * @buf: Buffer containing history line
 * @linecount: Line count
 *
 * Return: 0 on success, -1 on failure
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	char *temp;

	temp = strdup(buf);
	if (temp == NULL)
		return (-1);

	remove_comments(temp);

	if (strlen(temp) > 1)
	{
		if (add_node_end(&(info->history), temp, linecount) == NULL)
		{
			free(temp);
		}
		return (-1);
	}
	return (0);
}

/**
 * renumber_history - Renumber history linked list
 * @info: Pointer to info_t struct
 *
 * Return: 0 on success, -1 on failure
 */
int renumber_history(info_t *info)
{
	list_t *temp = info->history;
	int count = 1;

	while (temp != NULL)
	{
		temp->num = count;
		temp = temp->next;
		count++;
	}
	return (0);
}
