/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** create_connection
*/

#include "server.h"
#include "macro.h"

static int get_data_transfert_socket(const int com, t_user_infos *user)
{
	struct sockaddr_in client;
	socklen_t client_size;
	int socket;

	client_size = sizeof(client);
	if (user->transfert_mode == PASV) {
		send_reply(com, CONNECT_OPEN);
		return (accept(user->data_transfert_socket,
			(struct sockaddr *)&client, &client_size));
	}
	socket = create_socket(user->datas_transfert_port,
		inet_addr(user->client_ip), CLIENT, VERBOSE);
	if (socket == FD_ERROR)
		return (send_reply(com, CONNECT_FAIL), FAILURE);
	send_reply(com, CONNECT_OPEN);
	return (socket);
}

int connect_to_client(const int com, t_user_infos *user, const char *reply)
{
	int socket;

	if (user->connected != CONNECT)
		return (send_reply(com, reply), FD_ERROR);
	if (user->transfert_mode == NONE)
		return (send_reply(com, REQUEST_PORT), FD_ERROR);
	socket = get_data_transfert_socket(com, user);
	if (socket == FD_ERROR)
		return (FD_ERROR);
	printf(SOCKET_OPEN, user->server_ip, user->datas_transfert_port);
	return (socket);
}

int close_connection(const int com, const int socket, t_user_infos *user)
{
	close (socket);
	send_reply(com, CLOSE_CONNECTION);
	printf(SOCKET_CLOSE, user->server_ip, user->datas_transfert_port);
	return (SUCCESS);
}