#include "cli.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 * _strtok - split strings by delimiter
 * @str: string to split
 * @d: delimiter string
 * Return: pointer to array of splitted words
 */
char **_strtok(char *str, char *d)
{
	int i, j, z, n, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[i], d))
			i++;
		z = 0;
		while (!is_delim(str[i + z], d) && str[i + z])
			z++;
		s[j] = malloc((z + 1) * sizeof(char));
		if (!s[j])
		{
			for (z = 0; z < j; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			s[j][n] = str[i++];
		s[j][n] = 0;
	}

	s[j] = NULL;
	return (s);
}
