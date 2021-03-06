/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** transfert_data
*/

#include "server.h"
#include "macro.h"

int receive_file(const int com, char *cmd, t_user_infos *user)
{
	int socket = connect_to_client(com, user, STOR_NCONNECT);

	if (socket == FD_ERROR)
		return (FAILURE);
	if (create_file(cmd, socket) == ERROR)
		return (send_reply(com, FILE_UNWRITABLE), FAILURE);
	printf(STOR_LOGS, cmd, user->server_ip, user->datas_transfert_port);
	return (close_connection(com, socket, user));
}

int send_file(const int com, char *cmd, t_user_infos *user)
{
	int socket = connect_to_client(com, user, NOT_CONNECTED);

	if (socket == FD_ERROR)
		return (FAILURE);
	if (access(cmd, F_OK) == FD_ERROR ||
		read_file(cmd, socket) != SUCCESS) {
		close (socket);
		send_reply(com, FILE_NOT_EXIST);
		return (FAILURE);
	}
	printf(RETR_LOGS, cmd, user->server_ip, user->datas_transfert_port);
	return (close_connection(com, socket, user));
}

int do_ls(const int com, char *cmd, t_user_infos *user)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	int socket = connect_to_client(com, user, NOT_CONNECTED);

	if (socket == FD_ERROR)
		return (FAILURE);
	asprintf(&line, "ls -l %s | sed 1d", (cmd[0] ? cmd : "."));
	if (! line)
		return (FCT_FAIL("asprintf"),
			send_reply(com, LOCAL_ERR), ERROR);
	stream = popen(line, "r");
	free(line);
	if (! stream)
		return (FCT_FAIL("popen"), send_reply(com, LOCAL_ERR), ERROR);
	while (getline(&line, &len, stream) != -1)
		write(socket, line, strlen(line));
	pclose(stream);
	printf(LIST_LOGS, user->server_ip, user->datas_transfert_port);
	return (free(line), close_connection(com, socket, user));
}