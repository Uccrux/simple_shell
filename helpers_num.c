#include "shell.h"
/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nothing.
 */
void long_to_stri(long num, char *stri, int base)
{
	int index = 0, inNegative = 0;
	long cociente = num;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		stri[index++] = '0';

	if (stri[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			stri[index++] = letters[-(cociente % base)];
		else
			stri[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		stri[index++] = '-';

	stri[index] = '\0';
	str_reverse(stri);
}


/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *stri, char *character)
{
	int i = 0, counter = 0;

	for (; stri[i]; i++)
	{
		if (stri[i] == character[0])
			counter++;
	}
	return (counter);
}
