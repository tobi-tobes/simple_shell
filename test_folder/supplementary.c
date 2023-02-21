#include "shell.h"

/**
 * wordCount - counts the number of words in a string.
 * @str: input string
 *
 * Return: number of words
 */
int wordCount(char *str)
{
	int i, spaces = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			spaces++;
	}

	return (spaces);
}

/**
 * _strlen - finds the length of a given string
 * @s: input string
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int len = 0, i;

	for (i = 0; s[i]; i++)
	{
		len++;
	}
	return (len);
}

/**
 * _strcpy - copies one string onto another
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}

	dest[i++] = '\0';

	return (dest);
}

/**
 * tokenize - breaks a string into an array of words
 * @str: input string
 *
 * Return: array of words in the string
 */
char **tokenize(char *str)
{
	char *buffer, *portion, *del = " ";
	int length = 0, spaces = 0, i;
	char **args;

	length = _strlen(str);
	buffer = malloc(sizeof(char) * length);

	if (buffer == NULL)
		return (NULL);

	for (i = 0; str[i] != '\n'; i++)
	{
		buffer[i] = str[i];
	}
	buffer[i] = '\0';
	spaces = wordCount(buffer);
	args = malloc((sizeof(char *) * ((spaces + 1) + 1)));

	if (args == NULL)
		return (NULL);
	i = 0;
	portion = strtok(buffer, del);
	args[i] = malloc((sizeof(char) * _strlen(portion)) + 1);

	if (args[i] == NULL)
		return (NULL);
	_strcpy(args[i], portion);

	while (i < spaces)
	{
		i++;
		portion = strtok(NULL, del);
		args[i] = malloc((sizeof(char) * _strlen(portion)) + 1);

		if (args[i] == NULL)
			return (NULL);
		_strcpy(args[i], portion);
	}
	i++;
	args[i] = malloc(sizeof(char *));
	if (args[i] == NULL)
		return (NULL);
	args[i] = NULL;

	return (args);
}
