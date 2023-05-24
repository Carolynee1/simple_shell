#include "shell.h"

/**
 * init_info - initializes the info_t structure
 * @info: Pointer to the info_t structure
 */
void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
	info->line_count = 0;
	info->err_num = 0;
	info->line_count_flag = 0;
	info->fname = NULL;
	info->env = NULL;
	info->history = NULL;
	info->alias = NULL;
	info->environ = NULL;
	info->env_changed = 0;
	info->status = 0;
	info->cmd_buf = NULL;
	info->cmd_buf_type = CMD_NORM;
	info->readfd = STDIN_FILENO;
	info->histcount = 1;

}
/**
 * set_info - sets the values in the info_t structure
 * @info: Pointer to the info_t structure
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	init_info(info);
	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
		}
	}

	for (; info->argv && info->argv[i]; i++)
		;
	info->argc = i;

	replace_alias(info);
	replace_vars(info);
	}
}

/**
 * free_info - Frees the allocated memory in the info_t structure
 * @info: Pointer to the info_t Structure
 * @all: Flag indicating whether to frr all fields
 */
void free_info(info_t *info, int all)
{
	int i;

	if (info->argv)
	{
		for (i = 0; i < info->argc; i++)
			free(info->argv[i]);
		free(info->argv);
		info->argv = NULL;
	}

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		bfree((void **)info->environ);
		info->environ = NULL;
		if (info->cmd_buf)
			free(*(info->cmd_buf));
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

