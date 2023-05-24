#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	int fd;
	info_t info;
	
	{
	info.argc = argc;
	info.argv = argv;
	info.line_count_flag = 0;
	info.status = 0;
	info.histcount = 0;
	info.fname = NULL;
	info.env = NULL;
	info.readfd = 0;
	info.history = NULL;
	info.line_count = 0;
	info.path = NULL;
	info.err_num = 0;
	info.alias = 0;
	info.environ = 0;
	info.env_changed = 0;
	info.cmd_buf = NULL;
	info.cmd_buf_type = 0;
	}

	fd = 2;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Cant't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = fd;
	}
	/*Initialize shell history*/
	read_history(&info);
	/*populate environment list*/
	populate_env_list(&info);
	/*Main shell loop*/
	hsh(&info, argv);
	/*write shell history before exiting*/
	write_history(&info);
	/*free allocated memory*/
	free_info(&info, 1);

	return (EXIT_SUCCESS);
}
