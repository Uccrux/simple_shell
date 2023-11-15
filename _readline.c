#include "shell.h"

/**
* read_line - Reads a line from the prompt.
* @shell_data: struct for the program's data
*
* Return: number of bytes read.
*/
int _getline(shell_data *shell_data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *command_array[1] = {NULL};
	static char operator_array[1] = {'\0'};
	ssize_t read_bytes, index = 0;

	if (!command_array[0] || (operator_array[0] == '&' && errno != 0) ||
		(operator_array[0] == '|' && errno == 0))
	{
		for (index = 0; command_array[index]; index++)
		{
			free(command_array[index]);
			command_array[index] = NULL;
		}

		read_bytes = read(shell_data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (read_bytes == 0)
			return (-1);

		index = 0;
		do {
			command_array[index] = str_duplicate(_strtok(index ? NULL : buffer, "\n;"));
			index = split_logic_ops(command_array, index, operator_array);
		} while (command_array[index++]);
	}

	shell_data->input_line = command_array[0];
	for (index = 0; command_array[index]; index++)
	{
		command_array[index] = command_array[index + 1];
		operator_array[index] = operator_array[index + 1];
	}

	return (str_length(shell_data->input_line));
}

/**
* split_logic_ops - checks and split for && and || operators
* @command_array: array of the commands.
* @index: index in the command_array to be checked
* @operator_array: array of the logical operators for each previous command
*
* Return: index of the last command in the command_array.
*/
int split_logic_ops(char *command_array[], int index, char operator_array[])
{
	char *temp_str = NULL;
	int j;

	for (j = 0; command_array[index] != NULL  && command_array[index][j]; j++)
	{
		if (command_array[index][j] == '&' && command_array[index][j + 1] == '&')
		{
			temp_str = command_array[index];
			command_array[index][j] = '\0';
			command_array[index] = str_duplicate(command_array[index]);
			command_array[index + 1] = str_duplicate(temp_str + j + 2);
			index++;
			operator_array[index] = '&';
			free(temp_str);
			j = 0;
		}
		if (command_array[index][j] == '|' && command_array[index][j + 1] == '|')
		{
			temp_str = command_array[index];
			command_array[index][j] = '\0';
			command_array[index] = str_duplicate(command_array[index]);
			command_array[index + 1] = str_duplicate(temp_str + j + 2);
			index++;
			operator_array[index] = '|';
			free(temp_str);
			j = 0;
		}
	}
	return (index);
}
