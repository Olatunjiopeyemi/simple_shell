#include "main.h"

/**
 * input_buf -A function that buffers chained commands
 * @info: parameter struct
 * @buf: address of the buffer
 * @len: address of the length of the variable
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t length = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &length, stdin);
#else
		a = _getline(info, buf, &length);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - A function that gets a line
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t n = 0;
	char **bufers = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buffer, &length);
	if (n == -1)
		return (-1);
	if (length != NULL)
	{
		b = a;
		p = buffer + a;

		check_chain(info, buffer, &b, a, length);
		while (b < length)
		{
			if (is_chain(info, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bufers = p;
		return (_strlen(p));
	}

	*bufers = buffer;
	return (n);
}

/**
 * read_buf - A function that reads a buffer
 * @info: parameter struct
 * @buf: the buffer
 * @i: the size
 * Return: n
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t n = 0;

	if (*i != NULL)
		return (0);
	n = read(info->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}

/**
 * _getline - A function that gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: the address of a pointer to the buffer
 * @length: size of preallocated ptr buffer
 * Return: x
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t a, lent;
	size_t k;
	ssize_t r = 0, x = 0;
	char *p = NULL, *new = NULL, *c;

	p = *ptr;
	if (p && length)
		x = *length;
	if (a == lent)
		a = lent = 0;

	r = read_buf(info, buffer, &lent);
	if (r == -1 || (r == 0 && lent == 0))
		return (-1);

	c = _strchr(buffer + a, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : lent;
	new = _realloc(p, x, x ? x + k : k + 1);
	if (new == NULL)
		return (p ? free(p), -1 : -1);

	if (x)
		_strncat(new, buffer + a, k - a);
	else
		_strncpy(new, buffer + a, k - a + 1);

	x += k - a;
	a = k;
	p = new;

	if (length)
		*length = x;
	*ptr = p;
	return (x);
}

/**
 * sigintHandler -A function that blocks ctrl-C
 * @sig_num: the signal number
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
