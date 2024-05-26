#include "cli.h"

/**
 * input_buf - buffers chained commands
 * @info: structure Info
 * @buf: pointer to buffer
 * @len: pointer to length
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		r = getline(buf, &len_p, stdin);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			*len = r;

		}
	}
	return (r);
}


/**
 * get_input - gets a line minus the newline
 * @info: structure Info
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **p_buf = &(info->arg), *p;

	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		j = len;
		i = j + 1;
		if (i >= len)
			i = len = 0;
		*p_buf = p;
		return (strlen(p));
	}
	*p_buf = buf;
	return (r);
}

