#include "simpleshell.h"

/**
 * main - a shell program that works like a bash shell
 * @argc: arguments count
 * @argv: argument passed
 * Return: 0 (successful)
 */

int main(int argc, char **argv)
{
	char *prompt = "K&O->>";
	char *lineptr = NULL, *copy = NULL;
	char *exitmsg = "Disconnecting..";
	size_t n = 0;
	ssize_t charsread;
	const char *delimeter = " ";
	char *token;
	int i = 0, no_oftoks = 0;

	(void)argc;

	while (!0)
	{
		puts(prompt);
		charsread = getline(&lineptr, &n, stdin);

		if (charsread == -1)
		{
			puts(exitmsg);
			return (-1);
		}

		copy = malloc(sizeof(char) * charsread);
		if (!copy)
		{
			perror("sh: Memory allocation error");
			return (-1);
		}

		_strcpy(copy, lineptr);

		token = strtok(NULL, delimeter);

		while (token)
		{
			no_oftoks++;
			token = strtok(NULL, delimeter);
		}
		no_oftoks++;

		argv = malloc(sizeof(char *) * no_oftoks);
		token = strtok(copy, delimeter);

		while (token)
		{
		argv[i] = malloc(sizeof(char) * _strlen(token));
		_strcpy(argv[i], token);

		token = strtok(NULL, delimeter);
		}
		i++;
		argv[i] = NULL;

		handle_execution(argv);
	}

	free(copy);
	free(lineptr);

	return (0);
}
