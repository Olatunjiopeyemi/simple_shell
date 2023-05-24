#include "shell.h"

/**
 * _strcmp - compares two strangs.
 * @s1: string1
 * @s2: strang2
 *
 * Return: integer
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - program that concatenates two strings
 * @dest: buffer to the concatenated strings
 * @src: buffer with the strings
 *
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *buf = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (buf);
}

/**
 * starts_with - checks the string
 * @haystack: string to check
 * @needle: substring to find
 *
 * Return: pointer or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strlen - length of a string
 * @s: the string to check
 * Return: length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}
