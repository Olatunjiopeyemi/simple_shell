#include "main.h"

/**
 * get_environ - A function that returns the string array copy of our environ
 * @info: Structure containing potential arguments
 * Return: 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - A function that removes an environ variable
 * @info: Structure containing potential argument
 * @var: the string env var property
 * Return: 1 or 0
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *pointer;

	if (!node || !var)
		return (0);

	while (node != NULL)
	{
		pointer = starts_with(node->str, var);
		if (pointer && *pointer == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - A function that initialize a new environment variable
 * @info: Structure containing potential arguments
 * @var: the string environ variable
 * @value: the string environ variable value
 *  Return: 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pointer;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		pointer = starts_with(node->str, var);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
