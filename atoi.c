#include <main.h>

/**
 * interactive - a function that return true if interactive
 * @info: a struct address
 * Return: 0 or 1
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - a function that checks for delimeter
 * @c: the character to check
 * @delim: the delimeter
 * Return: 0 or 1
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - a function that checks for alphabet
 *@c: A character input
 *Return: 0 or 1
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - A function that converts a string into integer
 *@s: string to convert
 *Return: 0 or the converted number
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, product;
	unsigned int result = 0;

	for (a = 0;  s[a] != '\0' && flag != 2; i++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		product = -result;
	else
		product = result;

	return (product);
}
