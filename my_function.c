#include "simpleshell.h"

/**
 * _strcpy - a function that copies strings
 * @dest: destination to copy to
 * @src: th source where the string is copied from
 * Return: dest
 */

char *_strcpy(char *dest, const char *src)
{
	char *destptr = dest;

	for (; *src != '\0'; src++, destptr++)
	{
		*destptr = *src;
	}
	*destptr = '\0';
	return (dest);
}





/**
 * _strcat - afunction that concatenate 2 strings
 * @dest: concatenation destination
 * @src: concatenation source
 * Return: dest
 */

char *_strcat(char *dest, const char *src)
{
	char *destptr = dest;

	while (*destptr != '\0')
	{
		destptr++;
	}

	for (; *src != '\0'; src++, destptr++)
	{
		*destptr = *src;
	}
	*destptr = '\0';

	return (dest);
}





/**
 * _strlen - a function that returns the lengtyh of a string
 * @str: the string to be accessed
 * Return: the length
 */

size_t _strlen(const char *str)
{
	size_t length = 0;

	for (length = 0; str[length] != '\0'; length++)
	{

	}
	return (length);
}


/**
 * _strdup - a function that duplicate strings
 * @str: the string to be duplicated
 * Return: the duplicated string
 *
 */


char* _strdup(const char *str)
{
	size_t length = 0;
	const char *temp = str;
	char *dup, *new;

	if (!str)
		return (NULL);


	while (*temp++ != '\0')
	{
		length++;
	}

	dup = (char *)malloc((length + 1) * sizeof(char));

	if (!dup)
		return (NULL);

	new = dup;

	while (*str != '\0')
	{
		*new++ = *str++;
	}
	*new = '\0';

	return (dup);
}

