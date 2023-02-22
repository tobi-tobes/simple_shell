#include "shell.h"

/**
 * main - a UNIX command line interpreter.
 * @ac: argument count
 * @av: argument vector
 *
 * Return: exit status from exit function
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av)
{
	int loop = 1, check_mul_args;
	char *buffer = NULL;
	size_t n = 0;
	char **tokens;

	while (loop == 1 || loop == 2)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if (getline(&buffer, &n, stdin) >= 0)
		{
			if (buffer[0] != '\0' && strcmp(buffer, "\n") != 0)
			{
				check_mul_args = chck_mul_cmds(buffer);
				if (check_mul_args == 0)
				{
					tokens = tokenize(buffer, ' ');

					if (tokens != NULL)
						loop = call(tokens);
				}
				free_array(tokens);
			}
		}
		free(buffer);
	}
	exit(loop);
}
