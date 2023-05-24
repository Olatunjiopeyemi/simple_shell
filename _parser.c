#include "shell.h"

/**
 * is_cmd -> checks if file is executable
 * @info: struct info
 * @path: the file path
 * Return: 1 on success or 0 on failure
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars -> makes a copy of the characters
 * @pathstr: path to the string of characters
 * @start: index at the start
 * @stop: index at the end
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path -> checks the command in the path
 * @info: struct info
 * @pathstr: path to the string of characters
 * @cmd: command to check
 * Return: the fullpath of the command or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			pos = a;
		}
		a++;
	}
	return (NULL);
}
