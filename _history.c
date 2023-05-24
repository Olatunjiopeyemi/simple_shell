#include "main.h"

/**
 * get_history_file -  A function that gets a history file
 * @info: parameter struct
 * Return: a string
 */

char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (directory == NULL)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - A function that creates a file, or appends to file
 * @info: the parameter struct
 * Return: 1 or -1
 */

int write_history(info_t *info)
{
	ssize_t filedes;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filedes == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, filedes);
		_putfd('\n', filedes);
	}
	_putfd(BUF_FLUSH, filedes);
	close(filedes);
	return (1);
}

/**
 * renumber_history - A function that renumbers the history list
 * @info: Structure containing potential arguments
 * Return: histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

/**
 * build_history_list - A function that adds entry to a history list
 * @info: Structure containing potential arguments
 * @buf: The buffer
 * @linecount: the history linecount
 * Return: 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


/**
 * read_history - A function that reads history from file
 * @info: the parameter struct
 * Return: 0 or histcount
 */

int read_history(info_t *info)
{
	int a, last = 0, count = 0;
	ssize_t filedes, readlen, filesize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	filedes = open(filename, O_RDONLY);
	free(filename);
	if (filedes == -1)
		return (0);
	if (!fstat(filedes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	readlen = read(filedes, buffer, fsize);
	buffer[fsize] = 0;
	if (readlen <= 0)
		return (free(buffer), 0);
	close(filedes);
	for (a = 0; a < fsize; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(info, buffer + last, count++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buffer + last, count++);
	free(buffer);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
