#include "shell.h"

/**
 * initialize_info - Initializes the info structure.
 * @info: Pointer to the info_t structure.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 **/
void initialize_info(info_t *info, int argc, char *argv[])
{
	info->argc = argc;
	info->argv = argv;
	info->line_count_flag = 0;
	info->status = 0;
	info->histcount = 0;
	info->fname = NULL;
	info->env = NULL;
	info->readfd = 0;
	info->history = NULL;
	info->line_count = 0;
	info->path = NULL;
	info->err_num = 0;
	info->alias = 0;
	info->environ = 0;
	info->env_changed = 0;
	info->cmd_buf = NULL;
	info->cmd_buf_type = 0;
}

/**
 * handle_file_opening - Handles opening of a file.
 * @info: Pointer to the info_t structure.
 **/
void handle_file_opening(info_t *info)
{
	int fd = 2;

	if (info->argc == 2)
	{
		fd = open(info->argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit_with_error(126);
			if (errno == ENOENT)
			{
				print_error_message(info->argv[0], info->argv[1]);
				exit_with_error(127);
			}
			exit_with_error(EXIT_FAILURE);
		}
		info->readfd = fd;
	}
}
