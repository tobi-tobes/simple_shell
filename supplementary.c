#include "shell.h"

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
 * word_count - counts the number of words in a string.
 * @str: input string
 * @del: delimiter
 *
 * Return: number of words
 */
int word_count(char *str, char del)
{
	int i, spaces = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == del)
			spaces++;
	}

	return (spaces);
}

/**
 * _strtok - splits a string
 * @string: input string
 * @del: seperator character
 * @args: pointer to array of words
 * @length: number of words
 *
 * Return: array of words in the string
 */
char **_strtok(char **args, char *string, char del, int length)
{
	int i = 0, j, k = 0, count = 0;
	char sub_buf[1024];

	for (j = 0; string[j] != '\0'; j++)
	{
		if (string[j] == del)
		{
			sub_buf[k] = '\0';
			args[i] = malloc((sizeof(char) * count) + 1);
			strcpy(args[i], sub_buf);
			count = k = 0;
			i++;
			if (i <= length)
				continue;
			else
				break;
		}
		else
		{
			sub_buf[k] = string[j];
			count++;
			k++;
		}
	}
	sub_buf[k] = '\0';
	args[i] = malloc((sizeof(char) * count) + 1);
	_strcpy(args[i], sub_buf);

	i++;
	args[i] = malloc(sizeof(char *));

	if (args[i] == NULL)
		return (NULL);
	args[i] = NULL;

	return (args);
}

/**
 * tokenize - breaks a string into an array of words
 * @str: input string
 * @del: seperator character
 *
 * Return: array of words in the string
 */
char **tokenize(char *str, char del)
{
	char buffer[BUFSIZE];
	int spaces = 0, i;
	char **args;

	for (i = 0; str[i] != '\n' && str[i] != '\0'; i++)
	{
		buffer[i] = str[i];
	}
	buffer[i] = '\0';
	spaces = word_count(buffer, del);
	args = malloc((sizeof(char *) * ((spaces + 1) + 1)));

	if (args == NULL)
		return (NULL);
	args = _strtok(args, buffer, del, spaces);

	return (args);
}
