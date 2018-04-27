/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** manage_client
*/

#include "server.h"
#include "macro.h"

void send_reply(const int com, const char *msg)
{
	write(com, msg, strlen(msg));
	write(com, "\r\n", 2);
}

static char *get_host_ip(const int com)
{
	struct sockaddr_in server;
	int server_size;

	server_size = sizeof(server);
	if (getsockname(com, &server, (socklen_t *)&server_size) == FD_ERROR)
		return (FCT_FAIL("getsockname"), NULL);
	return (inet_ntoa(server.sin_addr));
}

static t_user_infos fill_user_infos(const struct sockaddr_in *client,
		int port, char *root)
{
	t_user_infos new_user = {
		root,
		NULL,
		strdup(inet_ntoa(client->sin_addr)),
		port,
		ntohs(client->sin_port),
		FD_ERROR,
		NULL,
		LOGIN,
		FD_ERROR,
		NONE
	};

	return (new_user);
}

static int quit_client(t_user_infos *user)
{
	printf("[*] Client from %s:%d exited\n", user->client_ip,
			user->client_port);
	if (user->login != NULL)
		free(user->login);
	free(user->client_ip);
	return (SUCCESS);
}

int one_client_loop(const int com, const struct sockaddr_in *client,
		int port, char *root)
{
	int state;
	t_user_infos new_user = fill_user_infos(client, port, root);

	if (com == FD_ERROR)
		return (FCT_FAIL("accept"), ERROR);
	new_user.server_ip = get_host_ip(com);
	if (new_user.server_ip == NULL)
		return (ERROR);
	send_reply(com, READY);
	while (1) {
		state = get_command(com, &new_user);
		if (state == ERROR)
			return (ERROR);
		else if (state == EXIT)
			return (quit_client(&new_user));
	}
	return (SUCCESS);
}