#include "main.h"

/**
 * _myhistory - A function that displays history list starting at 0
 * @info: A Struct contains potential arguments
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - A functions that sets an alias to a string
 * @info: A parameter struct
 * @str: string alias
 * Return: 0 or 1
 */
int unset_alias(info_t *info, char *str)
{
	char *a, b;
	int remove;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	remove = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (remove);
}

/**
 * set_alias - A function that sets an alias to a string
 * @info: A parameter struct
 * @str: stringed alias
 * Return: 0 or 1
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - A function that prints an alias string
 * @node: An alias node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - A function that mimics the alias builtin
 * @info: A Struct contains potential arguments
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		b = _strchr(info->argv[a], '=');
		if (b)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
