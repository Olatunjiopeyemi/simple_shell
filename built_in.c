#include "shell.h"

/**
 * _myexit - a function that aids the exits the shell
 * @info: a struct that contains potential arguments
 * Return: exits with an exit status or 0
 */
int _myexit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = _erratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - A function that changes the current directory of the process
 * @info: a Struct containing potential arguments.
 *  Return: 0
 */
int _mycd(info_t *info)
{
	char *a, *dir, buffer[1024];
	int _chdir;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			_chdir = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			_chdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		_chdir = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		_chdir = chdir(info->argv[1]);
	if (_chdir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - A function that changes the current directory of the process
 * @info: A Struct that contains potential arguments
 *  Return: 0
 */
int _myhelp(info_t *info)
{
	char **argarray;

	argarray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argarray);
	return (0);
}
