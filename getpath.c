#include "simpleshell.h"

/**
 * getpath - a function that gets the path of a given command
 * @command: the commad entered by the user
 * Return: a char value f command path
 */


char *getpath(char *command)
{
	char *path, *p_copy, *p_copytok, *commandpath;
	int commandlen, totallen;
	struct stat buffer;

	path = _getenv("PATH");

	if (path != NULL)
	{
		p_copy = _strdup(path);
		commandlen = _strlen(command);
		p_copytok = strtok(p_copy, ":");

		while (p_copytok)
		{
			totallen = _strlen(p_copytok);
			commandpath = malloc(commandlen + totallen + 2);
			_strcpy(commandpath, p_copytok);
			_strcat(commandpath, "/");
			_strcat(commandpath, command);
			_strcat(commandpath, "\0");

			if (stat(commandpath, &buffer) == 0)
			{
				free(p_copy);

				return (commandpath);
			}

			else 
			{
				free(commandpath);
				p_copytok = strtok(NULL, ":");
			}
		}
		free(p_copy);

		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}

