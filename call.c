#include "shell.h"

/**
 * call - calls function for shell
 * @args: array of arguments
 *
 * Return: value of functions or 2 on error
 */
int call(char **args)
{
	int i;
	b_t builtins[] = {
		{"exit", hsh_exit},
		{"env", hsh_env},
		{"setenv", hsh_setenv},
		{"unsetenv", hsh_unsetenv},
		{"cd", hsh_cd},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].command != NULL; i++)
	{
		if (_strcmp(args[0], builtins[i].command) == 0)
			return (builtins[i].p(args));
	}

	if (search_PATH(args))
		return (execute(args));

	else
	{
		perror("./hsh");
		return (2);
	}
}
