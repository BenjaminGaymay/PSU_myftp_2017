/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** basics
*/

#include "basics.h"
#include "macro.h"

char *replace_char(char *str, const char old, const char new)
{
	for (int i = 0 ; str[i] ; i++) {
		if (str[i] == old)
			str[i] = new;
	}
	return (str);
}

int read_file(const char *path, const int fd)
{
	FILE *file;
	size_t len = 0;
	char *line = NULL;

	if (path != NULL) {
		file = fopen(path, "r");
		if (! file)
			return (FCT_FAIL("fopen"), ERROR);
		while (getline(&line, &len, file) != -1)
			write(fd, line, strlen(line));
	}
	else {
		file = fdopen(fd, "r");
		if (! file)
			return (FCT_FAIL("fdopen"), ERROR);
		while (getline(&line, &len, file) != -1)
			write(1, line, strlen(line));
	}
	free(line);
	return (SUCCESS);
}