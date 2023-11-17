#include "shell.h"
static int status_non;
/**
*non_interactive - a command line interpreter function for non_interactive way
*@argv: args vector
*
*Return: void
*/
void non_interactive(char **argv)
{
char *line;
char **args;
int count = 1, i = 0, j = 0;
status_non = 0;
do {
line = read_line();
if (line == NULL)
{
exit(status_non);
}
else if (is_all_spaces(line) == 1)
{
free(line);
}
else
{
args = split_line(line, " \n\t;|&'\"`(){}><");
for (i = 0 ; args[i] != NULL ; i++)
{
if (_strncmp(args[i], "#", 1) == 0)
{
for (j = i ; args[j] != NULL ; j++)
{
free(args[j]);
args[j] = NULL;
}
break;
}
}
if (args[0] == NULL)
free(args);
else
status_non = execute_command(args, argv, count);
}
} while (1);
}
/**
 *get_status_non - Get the value of the status variable
 *
 *Return: int - the value of the status_non variable
 */
int get_status_non(void)
{
return (status_non);
}
