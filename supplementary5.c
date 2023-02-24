#include "shell.h"

/**
 * cd_getenv - gets env variable for cd function
 * @variable: variable to be fetched from environ
 *
 * Return: 0
 */
int cd_getenv(char *variable)
{
	int i, j, found;

	for (i = 0; environ[i] != NULL; i++)
	{
		found = 1;
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (variable[j] != environ[i][j])
			{
				found = 0;
				break;
			}
		}
		if (found)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * update_pwd - updates PWD env variable for cd function
 * @new_value: new value to update cd with
 *
 * Return: updated PWD
 */
void update_pwd(char *new_value)
{
	int loc;

	loc = cd_getenv("PWD");
	environ[loc] = _update_env_var(environ[loc], new_value);
}

/**
 * handle_cmd_sep - handles command separator for multiple commands
 * @string: string of commands and arguments
 *
 * Return: 1 or 2 on error
 */
int handle_cmd_sep(char *string)
{
	char **tokens, **cmds;
	int i = 1, j = 0, status, num_args;
	pid_t child_pid;

	cmds = tokenize(string, ';');

	if (cmds != NULL)
	{
		num_args = check_num_arg(cmds);
		while (i <= num_args)
		{
			tokens = tokenize(cmds[j], ' ');
			if (tokens != NULL)
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("./hsh");
					return (2);
				}
				if (child_pid == 0)
				{
					call(tokens);
					_exit(0);
				}
				else
				{
					wait(&status);
					free_array(tokens);
					i++;
					j++;
				}
			}
		}
	}
	free_array(cmds);
	return (1);
}

/**
 * chck_mul_cmds - check for multiple commands
 * @string: string of commands and arguments
 *
 * Return: return value of subfunctions
 */
int chck_mul_cmds(char *string)
{
	int i, j = 0;
	char buffer[BUFSIZE];

	for (i = 0; string[j] != '\0'; i++)
	{
		if (string[j] == ' ' && string[j - 1] == ';')
			j++;
		else if (string[j] == ' ' && string[j - 1] == '&')
			j++;
		else if (string[j] == ' ' && string[j - 1] == '|')
			j++;

		buffer[i] = string[j];
		j++;
	}
	buffer[i] = '\0';
	i = 0;

	if (strstr(string, ";") != NULL)
		return (handle_cmd_sep(buffer));

	return (0);
}

/**
 * reassign_environ - makes a copy of environ array for program's use
 * @environ: environ
 *
 * Return: a copy of environ variable or the original environ if failure
 */
char **reassign_environ(char **array)
{
	char **_environ;
	int size, i = 0;

	size = check_num_arg(array);
	_environ = malloc((sizeof(char *) * size) + 1);

	if (_environ == NULL)
		return (array);

	while (i < size)
	{
		_environ[i] = malloc((sizeof(char) * _strlen(array[i])) + 1);

		if (_environ[i] == NULL)
		{
			free(_environ);
			return (array);
		}
		_strcpy(_environ[i], array[i]);
		i++;
	}
	_environ[i] = NULL;

	return (_environ);
}
