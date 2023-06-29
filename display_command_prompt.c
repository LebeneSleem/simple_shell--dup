#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGUMENTS 10

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *command = NULL;
    size_t command_size = 0;
    ssize_t command_length;
    char *token;
    char *arguments[MAX_ARGUMENTS];
    int arg_count;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");  /* Display prompt */
        command_length = getline(&command, &command_size, stdin);

        if (command_length == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove the newline character at the end */
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;  /* Ignore empty commands */

        token = strtok(command, " ");
        arg_count = 0;

        while (token != NULL && arg_count < MAX_ARGUMENTS - 1)
        {
            arguments[arg_count] = token;
            token = strtok(NULL, " ");
            arg_count++;
        }
        arguments[arg_count] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            execvp(arguments[0], arguments);  /* Execute the command */
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);  /* Wait for the child process to finish */
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                printf("Command '%s' not found\n", command);  /* Print error message */
        }
    }

    free(command);
    return 0;
}

