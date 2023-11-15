#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} shell_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(shell_data  *shell_data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(shell_data  *shell_data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, shell_data  *shell_data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standar input*/
int _getline(shell_data  *shell_data);

/* split the each line for the logical operators if it exist */
int split_logic_ops(char *command_array[], int index, char operator_array[]);


/*======== expansions.c ========*/

/* expand variables */
void expand_variables(shell_data  *shell_data);
/* expand aliases */
void expand_alias(shell_data *shell_data);

/* append the string to the end of the buffer*/
int buf_add(char *buf, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(shell_data *shell_data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(shell_data *shell_data);


/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(shell_data *shell_data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(shell_data *shell_data);

/* Search for program in path */
int validate_program(shell_data *shell_data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **dirs);

/* Free the fields needed each loop */
void free_recurrent_data(shell_data *shell_data);

/* Free all field of the data */
void free_all_data(shell_data *shell_data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(shell_data *shell_data);

/* Change the current directory */
int builtin_cd(shell_data  *shell_data);

/* set the work directory */
int set_work_directory(shell_data  *shell_data, char *new_dir);

/* show help information */
int builtin_help(shell_data *shell_data);

/* set, unset and show alias */
int builtin_alias(shell_data *shell_data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(shell_data *shell_data);

/* create or override a variable of environment */
int builtin_set_env(shell_data *shell_data);

/* delete a variable of environment */
int builtin_unset_env(shell_data *shell_data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, shell_data *shell_data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, shell_data *shell_data);

/* Remove a key from the environment */
int env_remove_key(char *key, shell_data *shell_data);

/* prints the current environ */
void print_environ(shell_data *shell_data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *str);

/* Prints a string in the standar error */
int _printe(char *str);

/* Prints a string in the standar error */
int _print_error(int errorcode, shell_data *shell_data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_len(char *str);

/* Duplicates an string */
char *str_duplicate(char *stri);

/* Compares two strings */
int str_compare(char *str1, char *str2, int num);

/* Concatenates two strings */
char *str_concat(char *str1, char *str2);

/* Reverse a string */
void str_reverse(char *str);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_stri(long num, char *stri, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *stri, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int display_alias(shell_data *shell_data, char *alias_name);

/* get the alias name */
char *retrieve_alias(shell_data *shell_data, char *alias_name);

/* set the alias name */
int update_alias(char *alias_str, shell_data *shell_data);


#endif /* SHELL_H */
