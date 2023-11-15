#include "shell.h"

/**
 * display_alias - Displays or manipulates aliases.
 * @shell_data: struct for the program's data
 * @alias_name: name of the alias to be displayed
 * Return: zero on success, or other number if declared in the arguments
 */
int display_alias(shell_data *shell_data, char *alias_name)
{
	int i, j, alias_len;
	char temp_buffer[-1] = {'\0'};

	if (shell_data->alias_list)
	{
		alias_len = str_length(alias_name);
		for (i = 0; shell_data->alias_list[i]; i++)
		{
			if (!alias_name || (str_compare(shell_data->alias_list[i], alias_name, alias_len)
				&&	shell_data->alias_list[i][alias_len] == '='))
			{
				for (j = 0; shell_data->alias_list[i][j]; j++)
				{
					temp_buffer[j] = shell_data->alias_list[i][j];
					if (shell_data->alias_list[i][j] == '=')
						break;
				}
				temp_buffer[j + 1] = '\0';
				buffer_add(temp_buffer, "'");
				buffer_add(temp_buffer, shell_data->alias_list[i] + j + 1);
				buffer_add(temp_buffer, "'\n");
				_print(temp_buffer);
}
		}
	}

	return (0);
}

/**
 * retrieve_alias - Retrieves an alias.
 * @shell_data: struct for the program's data
 * @alias_name: name of the requested alias.
 * Return: zero on success, or other number if declared in the arguments
 */
char *retrieve_alias(shell_data *shell_data, char *alias_name)
{
	int i, alias_len;

	if (alias_name == NULL || shell_data->alias_list == NULL)
		return (NULL);

	alias_len = str_length(alias_name);

	for (i = 0; shell_data->alias_list[i]; i++)
	{
		if (str_compare(alias_name, shell_data->alias_list[i], alias_len) &&
			shell_data->alias_list[i][alias_len] == '=')
		{
			return (shell_data->alias_list[i] + alias_len + 1);
		}
	}

	return (NULL);

}

/**
 * * update_alias - Adds or updates an alias.
 * @alias_str: alias to be updated in the form (name='value')
 * @shell_data: struct for the program's data
 * Return: zero on success, or other number if declared in the arguments
 */
int update_alias(char *alias_str, shell_data *shell_data)
{
	int i, j;
	char temp_buffer[-1] = {'0'}, *temp_ptr = NULL;

	if (alias_str == NULL ||  shell_data->alias_list == NULL)
		return (1);

	for (i = 0; alias_str[i]; i++)
		if (alias_str[i] != '=')
			temp_buffer[i] = alias_str[i];
		else
		{
			temp_ptr = retrieve_alias(shell_data, alias_str + i + 1);
			break;
		}

	for (j = 0; shell_data->alias_list[j]; j++)
		if (str_compare(temp_buffer, shell_data->alias_list[j], i) &&
			shell_data->alias_list[j][i] == '=')
		{
			free(shell_data->alias_list[j]);
			break;
		}

	if (temp_ptr)
	{
		buffer_add(temp_buffer, "=");
		buffer_add(temp_buffer, temp_ptr);
		shell_data->alias_list[j] = str_duplicate(temp_buffer);
	}
	else
		shell_data->alias_list[j] = str_duplicate(alias_str);
	return (0);
}
