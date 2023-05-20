#include "shell.h"

/**
 * custom_exit - Exits the shell with a given exit status
 * @info: Structure containing potential arguements.used to maintain
 *	constant function prototype.
 * Return: Exits with a given exit status:
 *	-2 if info->argv[0] == "exit" and info->argv[1] exists.
 *	-1 if info->argv[0] == "exit" and info->argv[1] doesn't exist.
 *	1 if an illegal number is provided as an argument.
 */
int custom_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = atoi(info->argv[1]);
		if (exit_status == 0 && info->argv[1][0] != '0')
		{
			info->status = 2;
			print_error(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * custom_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0.
 */
int custom_cd(info_t *info)
{
	char *current_dir, *dir;
	char buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
	if (!dir)
	chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	} else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
		return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
	chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	} else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	} return (0);
}
/**
 * custom_help - Prints a message indicating that the help function
 *	is not yet implemented.
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *	Return: Always 0.
 */
int custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	-puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}
