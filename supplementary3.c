#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @variable: environment variable whose value to get
 *
 * Return: value of environment variable or NULL if not found
 */
char *_getenv(char *variable)
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
			return (&(environ[i][j + 1]));
	}
	return (NULL);
}

/**
 * _strcat - concatenates two strings
 * @dest: pointer to resulting appended string
 * @src: pointer to string to be appended to dest
 *
 * Return: appended dest string
 */
char *_strcat(char *dest, char *src)
{
	int length, i, j;

	length = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
		length++;
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[length] = src[j];
		length++;
	}

	dest[length] = '\0';

	return (dest);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size in bytes of the allocated space for ptr
 * @new_size: new size, in bytes of the new memory block
 *
 * Return: pointer to array if successful or NULL otherwise
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *np;
	unsigned int i;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		np = malloc(new_size);
		if (np == NULL)
			return (NULL);
		free(ptr);
		return (np);
	}
	if (new_size == old_size)
		return (ptr);
	np = malloc(new_size);
	i = 0;

	while (i < new_size && i < old_size)
	{
		np[i] = ((char *) ptr)[i];
		i++;
	}
	free(ptr);
	return (np);
}

/**
 * _update - updates a string in an argument array
 * @args: array of argument
 * @path: path to be copied to string
 *
 * Return: updated array with new string
 */
char **_update(char **args, char *path)
{
	unsigned int oldsize, newsize;

	oldsize = _strlen(args[0]) + 1;
	newsize = _strlen(path) + 1;
	args[0] = _realloc(args[0], oldsize, newsize);

	strcpy(args[0], path);
	return (args);
}

/**
 * search_PATH - searches the PATH for an inputted command
 * @args: array of arguments
 *
 * Return: array of arguments to be executed or NULL;
 */
int search_PATH(char **args)
{
	char *path;
	char **path_dir;
	char cwd_path[BUFSIZE], path_buf[BUFSIZE];
	int i;
	struct stat st;

	if (strstr(args[0], "/") != NULL)
		return (1);

	path = _getenv("PATH");
	_strcpy(path_buf, path);
	path_dir = tokenize(path_buf, ':');

	for (i = 0; path_dir[i] != NULL; i++)
	{
		_strcpy(cwd_path, path_dir[i]);
		_strcat(cwd_path, "/");
		_strcat(cwd_path, args[0]);
		if (stat(cwd_path, &st) == 0)
		{
			_update(args, cwd_path);
			free_array(path_dir);
			path = NULL;
			return (1);
		}
	}
	free_array(path_dir);
	path = NULL;

	return (0);
}
