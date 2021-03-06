/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** manage_reply
*/

#include "client.h"
#include "macro.h"

static int is_reply_end(const char *line)
{
	int i = 0;
	for ( ; line[i] && i < 3 ; i++)
		if (isdigit(line[i]) == 0)
			return (FAILURE);
	return (line[i] == ' ' || line[i] == '\0' ? SUCCESS : FAILURE);
}

static int is_valid_reply(char *line, char **reply)
{
	int ret;
	if (line[3] == ' ') {
		*reply = line;
		line[3] = '\0';
		ret = atoi(line);
		line[3] = ' ';
		return (ret);
	}
	return (ERROR);
}

int server_open(const int com)
{
	int result;
	socklen_t result_size;

	result_size = sizeof(result);
	getsockopt(com, SOL_SOCKET, SO_ERROR, &result, &result_size);
	if (result != 0)
		return (fprintf(stderr, "Error: server down\n"), ERROR);
	return (SUCCESS);
}

int wait_reply(const int com, char **reply)
{
	size_t len = 0;
	char *line = NULL;
	FILE *file = fdopen(dup(com), "r");

	if (! file)
		return (FCT_FAIL("fdopen"), ERROR);
	if (server_open(com) == ERROR)
		return (fclose(file), ERROR);
	while (getline(&line, &len, file) && is_reply_end(line) == FAILURE) {
		if (server_open(com) == ERROR)
			return (fclose(file), free(line), ERROR);
		if (line[0] != '\n')
			write(1, line, strlen(line));
	}
	write(1, line, strlen(line));
	return (fclose(file), is_valid_reply(line, reply));
}