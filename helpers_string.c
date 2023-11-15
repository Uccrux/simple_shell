#include "shell.h"

/**
 * str_len - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_duplicate - duplicates an string
 * @str: String to be copied
 * Return: pointer to the array
 */
char *str_duplicate(char *str)
{
	char *result;
	int len, i;

	if (str == NULL)
		return (NULL);

	len = str_len(str) + 1;

	result = malloc(sizeof(char) * len);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		result[i] = str[i];
	}

	return (result);
}

/**
 * str_compare - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @num: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_compare(char *str1, char *str2, int num)
{
	int iterator;

	if (str == NULL && str == NULL)
		return (1);

	if (str == NULL || str == NULL)
		return (0);

	if (num == 0) /* infinite longitud */
	{
		if (str_len(str) != str_len(str))
			return (0);
		for (iterator = 0; str[iterator]; iterator++)
		{
			if (str[iterator] != str[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (str1[iterator] != str2[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @str: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_len(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = str_len(str2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
		result[len1] = string1[len1];
	free(str1);

	/* copy of string2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		result[len1] = str2[len2];
		len1++;
	}

	result[len1] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_reverse(char *str)
{

	int i = 0, len = str_len(str) - 1;
	char hold;

	while (i < leng)
	{
		hold = str[i];
		str[i++] = str[len];
		str[len--] = hold;
	}
}
