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

char *get_ip_from_cmd(char *cmd)
{
	int i = 0;
	int start = 0;
	int coma = 0;

	while (cmd[start] && cmd[start] != '(')
		start += 1;
	for (i = start + 1 ; cmd[i] && coma != 4 ; i++) {
		if (cmd[i] == ',')
			coma += 1;
	}
	cmd[i - 1] = '\0';
	return (replace_char(&cmd[start + 1], ',', '.'));
}

int get_port_from_cmd(char *cmd, int pos)
{
	int i = 0;
	int start = 0;

	for (int coma = 0 ; cmd[start] && coma != 4 + pos ; start++)
		if (cmd[start] == ',')
			coma += 1;
	for (i = start + 1 ; cmd[i] ; i++)
		if (! isdigit(cmd[i]))
			break;
	cmd[i] = '\0';
	return (atoi(&cmd[start]));
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

int create_file(const char *path, const int fd)
{
	FILE *stream;
	size_t len = 0;
	char *line = NULL;
	int file_fd;

	stream = fdopen(fd, "r");
	if (! stream)
		return (FCT_FAIL("fdopen"), ERROR);
	file_fd = open(path, O_WRONLY | O_CREAT, 0644);
	while (getline(&line, &len, stream) != -1)
		write(file_fd, line, strlen(line));
	close(file_fd);
	return (SUCCESS);
}