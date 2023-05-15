#include "simpleshell.h"

/**
 * compare - compares two string
 * @str1: The first string in question
 * @str2: the string to compare str1 with
 * Return: 0 or 1
 */

int compare(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (1);
	else
		return (0);
}

/**
 * _getenv - a function that gets the environmental variable
 * @name: the name of the variable to check
 * Return: a pointer to the  value  in the environment, or NULL
 */

char *_getenv(const char *name)
{
	extern char **environ;
	char **env, *var;
	int i;

	while (*env)
	{
		env = environ;
		var = *env;

	i = 0;
	while (name[i] != '\0' && var[i] != '=' && name[i] == var[i])
		i++;

	if (name[i] == '\0' && var[i] == '=')
		return (&var[i +1]);
	env++;
	}
	return (NULL);

}



/**
 * main - body
 * Return: 0 or 1
 */

int main()
{
	const char *varname = "PATH";
	char *val = _getenv(varname);
	char *errmsg = "Environmental variable not found:";

	if (val)
	{
		puts(varname);
		puts("=");
		puts(val);
		puts("");
	}
	else
	{
		puts(errmsg);
		puts(varname);
	}
	return (0);

