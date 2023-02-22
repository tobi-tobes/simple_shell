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
	int loop = 1, check_mul_args, mode;
	char *buffer = NULL;
	size_t n = 0;
	char **tokens;

	while (loop == 1 || loop == 2)
	{
		mode = isatty(STDIN_FILENO);

		if (mode == 1)
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&buffer, &n, stdin) == -1)
		{
			return (0);
		}
		else
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
		buffer = NULL;
		n = 0;
	}
	exit(loop);
}
