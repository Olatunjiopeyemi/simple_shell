#include "shell.h"

/**
 * hsh -> shell
 * @info: pointer to the struct
 * @av: argument vector
 *
 * Return: 0 or 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int builtin_v = 0;

	while (s != -1 && builtin_v != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("KO$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, av);
			builtin_v = find_builtin(info);
			if (builtin_v == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_v == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_v);
}

/**
 * find_builtin -> builtin command
 * @info: struct info
 * Return: -1 or 0 or 1 or -2
 */
int find_builtin(info_t *info)
{
	int a, builtin_v = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			builtin_v = builtintbl[a].func(info);
			break;
		}
	return (builtin_v);
}

/**
 * find_cmd -> checks for command in PATH
 * @info: info struct
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd -> creates a child process
 * @info: info struct
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
