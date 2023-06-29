#include "shell.h"
void display_command_prompt(char **av, char **env)
{
    char *string = NULL;
    size_t n = 0;
    ssize_t character;
    int a, status;
    char *argv[] = {NULL, NULL};
    pid_t child_pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("simple_shell$  ");

        character = getline(&string, &n, stdin);
        if (character == -1)
        {
            free(string);
            exit(EXIT_FAILURE);
        }

        a = 0;
        while (string[a])
        {
            if (string[a] == '\n')
                string[a] = 0;
            a++;
        }

        argv[0] = string;

        child_pid = fork();
        if (child_pid == -1)
        {
            free(string);
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            if (execve(argv[0], argv, env) == -1)
                printf("%s: No such file or directory\n", av[0]);
            free(string); /*Free string before exiting child process*/
            exit(EXIT_FAILURE); /*Make sure to exit the child process after execve or error message*/
        }
        else
        {
            wait(&status);
	}
    }
            free(string); /*Free string after child process has terminated*/
}

