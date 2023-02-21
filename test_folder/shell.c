#include "shell.h"

/**
 * main - a UNIX command line interpreter.
 * @ac: argument count
 * @av: argument vector
 *
 * Return: always 0
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char**av) 
{
	char *buffer = NULL;
	size_t n = 10;
	char **tokens;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if (getline(&buffer, &n, stdin) == -1)
		{
			perror("./hsh: 1");
			continue;
		}
		tokens = tokenize(buffer);

		if (tokens == NULL)
		{
			perror("./hsh: 1");
			continue;
		}
		if (execute(tokens) == -1)
		{
			perror("./hsh: 1");
			free_array(tokens);
			continue;
		}
		free_array(tokens);
		free(buffer);
	}
	return (0);
}
