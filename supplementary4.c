#include "shell.h"

/**
 * rmv_from_array - removes a variable from an array
 * @array: array to be edited
 * @position: position of element to be removed
 *
 * Return: new array or NULL
 */
char **rmv_from_array(char **array, unsigned int position)
{
	char **np;
	unsigned int i, j, old_size, new_size;

	old_size = check_num_arg(array);
	new_size = old_size;
	np = malloc(sizeof(char *) * new_size);
	if (np == NULL)
	{
		perror("./hsh");
		return (array);
	}
	i = j = 0;

	while (i < new_size)
	{
		if (i != position)
		{
			np[j] = malloc((sizeof(char) * _strlen(array[i])) + 1);
			if (np[j] == NULL)
			{
				free(np);
				perror("./hsh");
				return (array);
			}
			_strcpy(np[j], array[i]);
			j++;
		}
		i++;
	}
	np[i] = NULL;
	free_array(array);

	return (np);
}

/**
 * add_to_array - adds a variable to an array
 * @array: array to be edited
 * @new_size: new size of array
 * @buffer: string to add to new element of array
 *
 * Return: new array or NULL
 */
char **add_to_array(char **array, unsigned int new_size, char *buffer)
{
	char **np;
	unsigned int i;

	np = malloc(sizeof(char *) * new_size);
	if (np == NULL)
	{
		perror("./hsh");
		return (array);
	}
	i = 0;

	while (array[i] != NULL)
	{
		np[i] = malloc((sizeof(char) * _strlen(array[i])) + 1);
		if (np[i] == NULL)
		{
			perror("./hsh");
			free(np);
			return (array);
		}
		_strcpy(np[i], (array[i]));
		i++;
	}
	np[i] = malloc((sizeof(char) * _strlen(buffer)) + 1);
	if (np[i] == NULL)
	{
		free(np);
		perror("./hsh");
		return (array);
	}
	_strcpy(np[i], buffer);
	np[i + 1] = NULL;
	free_array(array);

	return (np);
}

/**
 * _update_env - update environ
 * @env_array: array to be edited
 * @buffer: element to add to array
 *
 * Return: new array or NULL
 */
char **_update_env(char **env_array, char *buffer)
{
	unsigned int oldsize, newsize;

	oldsize = check_num_arg(env_array) + 1;
	newsize = oldsize + 1;
	env_array = add_to_array(env_array, newsize, buffer);

	return (env_array);
}

/**
 * _update_env_var - update environment variable
 * @env_var: variable to be edited
 * @variable: updated variable
 *
 * Return: new array or NULL
 */
char *_update_env_var(char *env_var, char *variable)
{
	unsigned int newsize;
	char *np, buffer[BUFSIZE];

	_strcpy(buffer, variable);

	newsize = _strlen(buffer);
	np = malloc((sizeof(char) * newsize) + 1);

	if (np == NULL)
	{
		perror("./hsh");
		return (env_var);
	}
	_strcpy(np, buffer);
	free(env_var);

	return (np);
}
