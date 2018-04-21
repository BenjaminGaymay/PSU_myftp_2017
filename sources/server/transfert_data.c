/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** transfert_data
*/

#include "server.h"
#include "macro.h"

int get_data_transfert_socket(const int com, t_user_infos *user)
{
	struct sockaddr_in client;
	socklen_t client_size;
	int socket;

	client_size = sizeof(client);
	if (user->transfert_mode == PASV) {
		send_reply(com, CONNECT_OPEN);
		return (accept(user->data_transfert_socket, (struct sockaddr *)&client, &client_size));
	}
	socket = create_socket(user->datas_transfert_port, inet_addr(user->client_ip), CLIENT, VERBOSE);
	if (socket == FD_ERROR)
		return (send_reply(com, CONNECT_FAIL), FAILURE);
	send_reply(com, CONNECT_OPEN);
	return (socket);
}

int connect_to_client(const int com, t_user_infos *user)
{
	int socket;

	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FD_ERROR);
	if (user->transfert_mode == NONE)
		return (send_reply(com, REQUEST_PORT), FD_ERROR);
	socket = get_data_transfert_socket(com, user);
	if (socket == FD_ERROR)
		return (FD_ERROR);
	printf(" > Client %s connected with datas transfert socket on port %d\n", user->server_ip, user->datas_transfert_port);
	return (socket);
}

int close_connection(const int com, const int socket, t_user_infos *user)
{
	close (socket);
	send_reply(com, CLOSE_CONNECTION);
	printf(" < Data transfert socket closed for %s on port %d\n", user->server_ip, user->datas_transfert_port);
	return (SUCCESS);
}

int receive_file(const int com, char *cmd, t_user_infos *user)
{
	int socket = connect_to_client(com, user);

	if (socket == FD_ERROR)
		return (FAILURE);
	if (create_file(cmd, socket) == ERROR)
		return (send_reply(com, FILE_ERROR), FAILURE);
	printf("\t~ File \"%s\" received from %s on port %d\n", cmd, user->server_ip, user->datas_transfert_port);
	return (close_connection(com, socket, user));
}

int send_file(const int com, char *cmd, t_user_infos *user)
{
	int socket = connect_to_client(com, user);

	if (socket == FD_ERROR)
		return (FAILURE);
	if (access(cmd, F_OK) == FD_ERROR || read_file(cmd, socket) != SUCCESS) {
		close (socket);
		send_reply(com, FILE_NOT_EXIST);
		return (FAILURE);
	}
	printf("\t~ File \"%s\" sent to %s on port %d\n", cmd, user->server_ip, user->datas_transfert_port);
	return (close_connection(com, socket, user));
}

int do_ls(const int com, char *cmd, t_user_infos *user)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	int socket = connect_to_client(com, user);

	(void)cmd;
	if (socket == FD_ERROR)
		return (FAILURE);
	stream = popen("ls --color", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	while (getline(&line, &len, stream) != -1)
		write(socket, line, strlen(line));
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	printf("\t~ List from current directory sent to %s on port %d\n", user->server_ip, user->datas_transfert_port);
	return (close_connection(com, socket, user));
}