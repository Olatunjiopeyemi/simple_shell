#include "main.h"

/**
 * _erratoi - A function that converts a string into an integer
 * @s: the string to be converted
 * Return: 0,-1 or the converted integer
 */

int _erratoi(char *s)
{
	int a = 0;
	unsigned long int product = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			product *= 10;
			product += (s[a] - '0');
			if (product > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (product);
}

/**
 * print_error - A function that prints out an error message
 * @info: the parameter & return info struct
 * @estr: A string containing the specified error type
 * Return: 0,-1 or the converted number
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - A function that prints a decimal number in base 10
 * @input: the input
 * @fd: the file descriptor written into
 * Return: The number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, i = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		i++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			i++;
		}
		current %= a;
	}
	__putchar('0' + current);
	i++;

	return (i);
}

/**
 * convert_number - A function that clones itoa
 * @num: the number
 * @base: the base
 * @flags: the argument flags
 * Return: a string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - A function that replaces instances
 * @buf: the address of the string to be replaced
 * Return: 0;
 */

void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
