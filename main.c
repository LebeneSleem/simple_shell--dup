#include "shell.h"

/**
 * main - Shell entry point
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variable
 * Return: 0 (Success)
 */

int main(int ac, char **av, char **env)
{


	if (ac == 1)
		display_command_prompt(av, env);
	return (0);
}
