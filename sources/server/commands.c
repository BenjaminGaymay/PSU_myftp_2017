/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** commands
*/

#include "server.h"
#include "macro.h"

int login(const int com, char *login, int *connected)
{
	if (strcmp(login, "Anonymous") != SUCCESS)
		return (send_reply(com, BAD_LOG), FAILURE);
	*connected = PASSWORD;
	return (send_reply(com, GOOD_LOGIN), SUCCESS);
}

int password(const int com, char *pass, int *connected)
{
	if (strcmp(pass, "") != SUCCESS)
		return (send_reply(com, BAD_PASS), FAILURE);
	if (*connected == LOGIN)
		return (send_reply(com, NEED_ACC), FAILURE);
	else if (*connected == CONNECT)
		return (send_reply(com, ALREADY_CONNECTED), FAILURE);
	*connected = CONNECT;
	return (send_reply(com, CONNECTED), SUCCESS);
}

int do_cwd(const int com, char *cmd, int *connected)
{
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir(cmd) == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	send_reply(com, FILE_OKAY);
	return (SUCCESS);
}

int cdup(const int com, char *cmd, int *connected)
{
	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir("..") == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int exit_ftp(const int com, char *cmd, int *connected)
{
	(void)cmd;
	*connected = FAILURE;
	send_reply(com, LOGOUT);
	return (safe_close(com, EXIT));
}

int delete_file(const int com, char *file, int *connected)
{
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	remove(file);
	send_reply(com, FILE_OKAY);
	return (SUCCESS);
}

int do_pwd(const int com, char *cmd, int *connected)
{
	FILE *stream;
	char *path = NULL;
	char *reply;
	size_t len = 0;

	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);

	stream = popen("pwd", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	getline(&path, &len, stream);
	path[strlen(path) - 1] = '\0';
	asprintf(&reply, "257 \"%s\" created.\n", path);
	if (! reply)
		return (FCT_FAIL("asprintf"), ERROR);
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	send_reply(com, reply);
	free(reply);
	free(path);
	return (SUCCESS);
}

int port(const int com, char *cmd, int *connected)
{
	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	printf(" ~ Active mode enable for data transfer\n");
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int pasv(const int com, char *cmd, int *connected)
{
	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	printf(" ~ Passive mode enable for data transfer\n");
	send_reply(com, PASSIVE);
	return (SUCCESS);
}

int show_help(const int com, char *cmd, int *connected)
{
	t_ptr_fct tmp;
	t_ptr_fct *commands = get_cmd_ptr();

	(void)connected;
	for (int i = 0 ; i < 19 ; i++) {
		tmp = commands[i];
		if (cmd[0] == '\0' && i == 13)
			printf("\n%s\n", HELP_DATA);
		if (cmd[0] == '\0' || strncmp(cmd, tmp.name, strlen(tmp.name)) == SUCCESS)
			printf("%s", tmp.help);
	}

	send_reply(com, HELP);
	return (SUCCESS);
}

int noop(const int com, char *cmd, int *connected)
{
	(void)cmd;
	(void)connected;
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int receive_file(const int com, char *cmd, int *connected)
{
	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	send_reply(com, CONNECT_OPEN);
	// RECEPTION PUIS send_reply(com, CLOSE_CONNECTION);
	return (SUCCESS);
}

int send_file(const int com, char *cmd, int *connected)
{
	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	send_reply(com, CONNECT_OPEN);
	// ENVOI PUIS send_reply(com, CLOSE_CONNECTION);
	return (SUCCESS);
}

int do_ls(const int com, char *cmd, int *connected)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;

	(void)cmd;
	if (*connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);

	stream = popen("ls", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	while (getline(&line, &len, stream) != -1)
		printf("%s", line);
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	send_reply(com, CONNECT_OPEN);
	// ENVOI PUIS send_reply(com, CLOSE_CONNECTION);
	return (SUCCESS);
}