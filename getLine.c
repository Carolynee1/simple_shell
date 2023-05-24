#include "shell.h"
/**
 * input_buf - Read input from stdin into a buffer
 * @info: Pointer to the info_t struct
 * @buf: Pointer to the buffer
 * @len: Pointer to the length of the buffer
 *
 * Return: The number of characters read from stdin
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->line_count_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * get_input - Get input from stdin
 * @info: pointer to the info_t struct
 *
 * Return: The number of characters read from stdin
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		size_t j = i;

		p = buf + i;
		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Read data from a file descriptor into a buffer
 * @info: Pointer to the info_t struct
 * @buf: Pointer to the buffer
 * @i: Pointer to the index of the buffer
 *
 * Return: The number of characters read from the file descriptor
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r > 0)
	{
		*i = r;
		return (r);
	}
	return (-1);
}

/**
 * sigintHandler - signal handler fo SIGINT
 * @sig_num: signal number
 */
void sigintHandler(int sig_num __attribute__((unused)))
{
	signal(SIGINT, sigintHandler);
	_putchar('\n');
	_puts("$");
	fflush(stdout);
}

/**
 * _getline - get a line from a buffer
 * @info: Pointer to the info_t struct
 * @ptr: Pointer to the buffer
 * @length: Pointer to the length of the buffer
 *
 * Return: The length of the line
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	ssize_t n __attribute__((unused));
	size_t i, len;
	char **p = ptr;

	if (length == 0)
	{
		*ptr = NULL;
		*length = 0;
		return (-1);
	}
	for (i = 0; i < *length; i++)
	{
		if (p[i] '\n')
		break;
	}
	if (i == *length)
	{
		if (info->cmd_buf_type == CMD_NORM)
			info->histcount++;
		*length = 0;
		return (0);
	}
	len = i;
	*length -= len + 1;
	p[len] = '\0';
	*ptr = *p + len + 1;

	if (info->cmd_buf_type == CMD_NORM)
		info->histcount++;

	return (len);
}

