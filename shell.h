#ifndef SHELL_H
#define SHELL_H

#define INPUT_SIZ 1024
#define CHUNK_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

extern char **environ;

int _strlen(char *str);
int _strcmp(char *str_1, char *str_2);
void show_prompt(void);
char *_getinline(void);
void run_cmd(char *input);
void exit_cmd(void);
void print_env(void);
char _getinput(void);
#endif
