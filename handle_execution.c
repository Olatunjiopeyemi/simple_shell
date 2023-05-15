#include "simplehshell.h"

/**
 * handle_execution - a function that handles exection process of a command
 * @argv: The command entered
 */

void handle_execution(char **argv)
{
	char *command;
	char *givencommand;

	if (argv != NULL)
	{
		command = argv[0];
		givencommand = getpath(command);


		if (execve(givencommand, argv, NULL) == -1)
			perror("Error:");
	}
}
