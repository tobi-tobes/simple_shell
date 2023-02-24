#include "shell.h"

/**
 * hsh_exit - exits the shell
 * @args: array of arguments
 *
 * Return: 0 or exit status or 2 if error
 */
int hsh_exit(char **args)
{
	int exit_status, num;

	num = check_num_arg(args);

	if (num == 1)
		return (0);

	else if (num == 2)
	{
		exit_status = _atoi(args[1]);
		if (exit_status >= 0)
			return (exit_status);

	}
	perror("./hsh: exit");
	return (2);
}

/**
 * hsh_env - prints the current environment
 * @args: array of arguments
 *
 * Return: 1
 */
int hsh_env(char **args)
{
	int i, length;
	(void) args;

	for (i = 0; environ[i] != NULL; i++)
	{
		length = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], length);
		write(STDOUT_FILENO, "\n", 1);
	}

	return (1);
}

/**
 * hsh_setenv - updates or adds a variable to the current environment
 * @args: array of arguments
 *
 * Return: 1 or 2 if error
 */
int hsh_setenv(char **args)
{
	int i, j, found, num_args;
	char buffer[BUFSIZE];

	num_args = check_num_arg(args);

	if (num_args == 3)
	{
		_strcpy(buffer, args[1]);
		_strcat(buffer, "=");
		_strcat(buffer, args[2]);
		for (i = 0; environ[i] != NULL; i++)
		{
			found = 1;
			for (j = 0; environ[i][j] != '='; j++)
			{
				if (args[1][j] != environ[i][j])
				{
					found = 0;
					break;
				}
			}
			if (found)
			{
				environ[i] = _update_env_var(environ[i], buffer);
				return (1);
			}
		}
		environ = _update_env(environ, buffer);
		return (1);
	}
	perror("./hsh: setenv");
	return (2);
}

/**
 * hsh_unsetenv - removes a variable from the current environment
 * @args: array of arguments
 *
 * Return: 1 or 2 if error
 */
int hsh_unsetenv(char **args)
{
	int i, j, found, num_args;
	unsigned int position;

	num_args = check_num_arg(args);

	if (num_args == 2)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			found = 1;
			for (j = 0; environ[i][j] != '='; j++)
			{
				if (args[1][j] != environ[i][j])
				{
					found = 0;
					break;
				}
			}
			if (found)
			{
				position = i;
				environ = rmv_from_array(environ, position);
				return (1);
			}
		}
		perror("./hsh: unsetenv");
		return (2);
	}
	perror("./hsh: unsetenv");
	return (2);
}

/**
 * hsh_cd - changes working directory
 * @args: array of arguments
 *
 * Return: 1 or 2 if error
 */
int hsh_cd(char **args)
{
	int num_args;
	static char previous[BUFSIZE];
	char *next, next_buf[BUFSIZE];

	num_args = check_num_arg(args);
	if (num_args == 1)
	{
		getcwd(previous, 1024);
		next = _getenv("HOME");
		_strcpy(next_buf, next);
		if (chdir(next_buf) == -1)
		{
			perror("./hsh: cd");
			return (2);
		}
		update_pwd(next_buf);
		return (1);
	}
	else if (num_args == 2)
	{
		if (_strcmp(args[1], "-") == 0)
		{
			write(STDOUT_FILENO, previous, _strlen(previous));
			write(STDOUT_FILENO, "\n", 1);
			_strcpy(next_buf, previous);
		}
		else
			_strcpy(next_buf, args[1]);

		getcwd(previous, 1024);
		if (chdir(next_buf) == -1)
		{
			perror("./hsh: cd");
			return (2);
		}
		update_pwd(next_buf);
		return (1);
	}
	perror("./hsh: cd");
	return (2);
}
