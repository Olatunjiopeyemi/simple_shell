#include "shell.h"

/**
 * bfree -> frees buffer
 * @ptr: buffer to free
 * Return: 1 on success or 0 on failure
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
