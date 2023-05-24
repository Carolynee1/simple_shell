#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: converted number on success, -1 on error
 */
int _erratoi(char *str)
{
	int res = 0;

	if (!str)
		return (-1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @info: pointer to the info_t struct
 * @msg: the error message to be printed
 */
void print_error(info_t *info, char *msg)
{
	char *line_count_str = convert_number(info->line_count, CONVERT_UNSIGNED, 0);
	char *err_num_str = convert_number(info->err_num, CONVERT_UNSIGNED, 0);

	_eputs(info->fname);
	_eputs(":");
	_eputs(line_count_str);
	_eputs(":");
	_eputs("Error: ");
	_eputs(msg);
	_eputs(":");
	_eputs(err_num_str);
	_eputs("\n");

	free(line_count_str);
	free(err_num_str);
}

/**
 * print_d - prints a decimal number to the specified file descriptor
 * @fd: the file descriptor
 * @num: the number to be printed
 *
 * Return: 0 on success, -1 on failure
 */
int print_d(int fd, int num)
{
	char *num_str = convert_number(num, 0, 0);

	if (num_str)
	{
		_puts(num_str);
		_putsfd("\n", fd);

		free(num_str);
	}
	else
	{
		print_error(INFO, "print_d failed");
		return (-1);
	}
	return (0);
}

/**
 * convert_number - converts a number to a string representation
 * @num: the number to be converted
 * @flags: flags for conversion options
 * @width: minimum width of the resulting string
 *
 * Return: the converted number as a string
 */
char *convert_number(long int num, int flags, int width)
{
	char *res;
	int i, len, neg;
	long int temp;

	if (flags & CONVERT_UNSIGNED)
	{
		neg = 0;
		temp = num;
	}
	else
	{
		neg = (num < 0) ? 1 : 0;
		temp = (neg) ? -num : num;
	}
	len = (temp == 0) ? 1 : 0;
	while (temp != 0)
	{
		temp /= 10;
		len++;
	}
	if (neg)
		len++;
	len = (len < width) ? width : len;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		print_error(INFO, "malloc failed");
		return (NULL);
	}
	res[len] = '\0';
	temp = (flags & CONVERT_LOWERCASE) ? 32 : 0;
	for (i = len - 1; i >= neg; i--)
	{
		res[i] = (num % 10) + '0' + temp;
		num /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
/**
 * remove_comments - removes comments from a line
 * @line: the to modify
 */
void remove_comments(char *line)
{
	int i = 0;
	int in_quotes = 0;

	while (line[i])
	{
		if (line[i] == '#' && !in_quotes)
		{
			line[i] = '\0';
			break;
		}
			else if (line[i] == "");
		{
			in_quotes = !in_quotes;
		}
		i++;
	}
}
