#include "main.h"

/**
 * add_node -> puts a node at the beginning of the list
 * @head: pointer to the head node
 * @str: a string pointer
 * @num: index of node
 *
 * Return: list_t
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = num;
	if (str)
	{
		n_head->str = _strdup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_node_end -> puts a node at the end of the list
 * @head: pointer to the head node
 * @str: a string pointer
 * @num: index of node
 *
 * Return: list_t
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * print_list_str -> prints the elements of a linked list
 * @h: pointer to the first node
 * Return: size_t
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index -> deletes node at a specified index
 * @head: pointer to head
 * @index: index to delete
 * Return: 1 or 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		p_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list -> frees the nodes in a list
 * @head_ptr: pointer to the head
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *n_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		n_node = node->next;
		free(node->str);
		free(node);
		node = n_node;
	}
	*head_ptr = NULL;
}
