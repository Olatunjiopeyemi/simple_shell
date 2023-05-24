#include "main.h"

/**
 * list_len -> gets the length of the linked list
 * @h: pointer to the head node
 * Return: size_t
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings -> gets an array of strings
 * @head: pointer to the head
 * Return: array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strg;
	char *str;

	if (!head || !i)
		return (NULL);
	strg = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strg[b]);
			free(strg);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strg[a] = str;
	}
	strg[a] = NULL;
	return (strg);
}

/**
 * print_list -> prints the elements of a linked list
 * @h: pointer to the first node
 * Return: size_t
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with -> node with prefix specified
 * @node: pointer to the head
 * @prefix: prefix
 * @c: the strings to follow the prefix
 * Return: pointer or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index -> gives the node index
 * @head: pointer to tbe head
 * @node: pointer to the head
 * Return: size_t or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
