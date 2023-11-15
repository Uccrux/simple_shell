#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(shell_data *shell_data)
{
	int k, j;
	char line[BUF_SIZE] = {0}, expansion[BUF_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buf_add(line, data->input_line);
	for (k = 0; line[k]; k++)
		if (line[k] == '#')
			line[k--] = '\0';
		else if (line[k] == '$' && line[k + 1] == '?')
		{
			line[k] = '\0';
			long_to_str(errno, expansion, 10);
			buf_add(line, expansion);
			buf_add(line, data->input_line + k + 2);
		}
		else if (line[k] == '$' && line[k + 1] == '$')
		{
			line[i] = '\0';
			long_to_str(getpid(), expansion, 10);
			buf_add(line, expansion);
			buf_add(line, data->input_line + k + 2);
		}
		else if (line[k] == '$' && (line[k + 1] == ' ' || line[k + 1] == '\0'))
			continue;
		else if (line[k] == '$')
		{
			for (j = 1; line[k + j] && line[k + j] != ' '; j++)
				expansion[j - 1] = line[k + j];
			temp = env_get_key(expansion, data);
			line[k] = '\0', expansion[0] = '\0';
			buf_add(expansion, line + k + j);
			temp ? buffer_add(line, temp) : 1;
			buf_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(shell_data *shell_data)
{
	int k, j, was_expanded = 0;
	char line[BUF_SIZE] = {0}, expansion[BUF_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buf_add(line, data->input_line);

	for (k = 0; line[k]; k++)
	{
		for (j = 0; line[k + j] && line[k + j] != ' '; j++)
			expansion[j] = line[k + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + k + j);
			line[k] = '\0';
			buffer_add(line, temp);
			line[str_len(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buf, char *str_to_add)
{
	int len, k;

	len = str_len(buf);
	for (k = 0; str_to_add[k]; k++)
	{
		buf[len + k] = str_to_add[k];
	}
	buf[len + k] = '\0';
	return (len + k);
}
