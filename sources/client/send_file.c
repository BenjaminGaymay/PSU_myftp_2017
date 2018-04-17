/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** send_file
*/

#include "client.h"
#include "macro.h"

int send_file(const int com, char *cmd)
{
	FILE *file;
	size_t len = 0;
	char *line = NULL;
	char *path = strndup(&cmd[5], strlen(&cmd[5]));

	if (access(path, F_OK) == -1) {
		fprintf(stderr, "Error: file '%s' doesn't exist\n", path);
		return (free(path), ERROR);
	}

	file = fopen(path, "r");
	free(path);
	if (! file)
		return (FCT_FAIL("fopen"), ERROR);

	while (getline(&line, &len, file) != -1)
		write(com, line, strlen(line));
	//fclose(file);
	free(line);
	return (SUCCESS);
}
