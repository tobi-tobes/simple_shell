#include "shell.h"

/**
 * free_array - frees an array of strings and its contents
 * @array: array to be freed
 *
 * Return: nothing
 */
void free_array(char **array)
{
	int i;

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}
	free(array);
}

/**
 * _strcmp - compares two strings
 * @s1: pointer to first string to be compared
 * @s2: pointer to second string to be compared
 *
 * Return: 0 if strings are the same, <0 if s1 is longer, >0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] == s2[i])
			continue;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * execute - executes the given function
 * @tokens: array of arguments
 *
 * Return: no return or -1 on error
 */
int execute(char **tokens)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("./hsh");
		return (2);
	}
	if (child_pid == 0)
	{
		if (execve(tokens[0], tokens, environ) == -1)
		{
			perror("./hsh");
			return (2);
		}
	}
	else
		wait(&status);

	return (1);
}

/**
 * _atoi - convert a string to an integer
 * @s: string to be converted
 *
 * Return: converted number if successful, 0 if error
 */
int _atoi(char *s)
{
	int i, num;

	num = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = (num * 10) + (s[i] - '0');
		else
			return (-1);
	}
	return (num);
}

/**
 * check_num_arg - checks the number of arguments in an array
 * @args: array of arguments
 *
 * Return: number of arguments
 */
int check_num_arg(char **args)
{
	int i, length = 0;

	for (i = 0; args[i] != NULL; i++)
	{
		length++;
	}
	return (length);
}
