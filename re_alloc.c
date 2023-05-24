#include "main.h"

/**
 * _memset -> sets memory to a specific byte
 * @s: pointer to memory
 * @b: specified byte
 * @n: number of bytes filled
 * Return: pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * _realloc -> re-allocates memory
 * @ptr: pointer
 * @old_size: size of old block
 * @new_size: size of new block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *c;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		c[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (c);
}

/**
 * ffree -> frees a pointer to a string
 * @pp: pointer to the string
 */
void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}
