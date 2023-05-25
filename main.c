#include "shell.h"

/**
 * cleanup - Frees allocated resources and closes the file descriptor.
 * @info: Pointer to the info_t structure.
 * @fd: File descriptor.
 **/
void cleanup(info_t *info, int fd)
{
	free_info(info, 1);

	if (fd != 2)
		close(fd);
}

/**
 * run_shell - Executes the shell logic.
 * @info: Pointer to the info_t structure.
 * @argv: Array of command-line arguments.
 **/
void run_shell(info_t *info, char *argv[])
{
	hsh(info, argv);
}

/**
 * print_error_message - Prints an error message.
 * @program_name: Name of the program.
 * @file_name: Name of the file.
 **/
void print_error_message(char *program_name, char *file_name)
{
	_eputs(program_name);
	_eputs(": 0: Can't open ");
	_eputs(file_name);
	_eputchar('\n');
	_eputchar(BUF_FLUSH);
}

/**
 * exit_with_error - Exits the program with an error code.
 * @exit_code: The exit code.
 **/
void exit_with_error(int exit_code)
{
	exit(exit_code);
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: Exit status.
 **/
int main(int argc, char *argv[])
{
	info_t info;
	int fd = 2;

	initialize_info(&info, argc, argv);
	handle_file_opening(&info);

	read_history(&info);
	populate_env_list(&info);
	run_shell(&info, argv);
	write_history(&info);
	cleanup(&info, fd);

	return (EXIT_SUCCESS);
}

