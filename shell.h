#ifndef SHELL_H_
#define SHELL_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>


#define BUFFER_SIZE 1024
#define Max_Arguments 20
#define PATH_MAX 100

/**Shell entry point**/
int main(int ac, char **av, char **env);

void swap_int(int *a, int *b);
void bubble_sort(int *array, size_t size);
void prompt_command(char **av, char **env);

/**custom alternate functions used*/
int string_len(char *string);
char *string_cpy(char *dest, char *src);
int string_cmp(char *s1, char *s2);
char *_strdup(char *str);

void _env(char **env);
char *handle_path(char *command);
void handle_arguments(char *lineptr, char **argv);
void handle_command_execution(char **argv, char **env);
void display_command_prompt(char **av, char **env);

#endif
