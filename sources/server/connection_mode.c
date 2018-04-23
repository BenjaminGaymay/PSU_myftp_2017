/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** connection_mode
*/

#include "server.h"
#include "macro.h"

void clear_old_socket(t_user_infos *user)
{
	close(user->data_transfert_socket);
	user->data_transfert_socket = FD_ERROR;
}

int port(const int com, char *cmd, t_user_infos *user)
{
	int port_2 = get_port_from_cmd(cmd, 1);
	int port_1 = get_port_from_cmd(cmd, 0);

	clear_old_socket(user);
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	printf(" ~ Active mode enable for datas transfert\n");
	user->datas_transfert_port = port_1 * 256 + port_2;
	user->client_ip = strdup(get_ip_from_cmd(cmd));
	if (! user->client_ip)
		return (send_reply(com, CONNECT_FAIL), FAILURE);
	send_reply(com, CMD_OKAY);
	user->transfert_mode = PORT;
	return (SUCCESS);
}

int find_free_port(t_user_infos *user)
{
	int port_1;
	int port_2;

	while (user->data_transfert_socket == FD_ERROR) {
		port_1 = rand() % 256;
		port_2 = rand() % 256;
		user->datas_transfert_port = port_1 * 256 + port_2;
		user->data_transfert_socket = create_socket(
			user->datas_transfert_port, INADDR_ANY, SERVER, QUIET);
	}
	return (port_2);
}

char *generate_pasv_reply(t_user_infos *user, char *cpy_ip, int port_2)
{
	int port_1 = (user->datas_transfert_port - port_2) / 256;
	char *reply;

	cpy_ip = strdup(user->server_ip);
	if (! cpy_ip)
		return (FCT_FAIL("strdup"), NULL);
	asprintf(&reply, "227 Entering Passive Mode (%s,%d,%d).\n",
		replace_char(cpy_ip, '.', ','), port_1 , port_2);
	if (! reply)
		return (FCT_FAIL("asprintf"), NULL);
	return (reply);
}

int pasv(const int com, char *cpy_ip, t_user_infos *user)
{
	char *reply;
	int port_2;

	clear_old_socket(user);
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	port_2	= find_free_port(user);
	printf(" ~ Passive mode enable for datas transfert\n");
	reply = generate_pasv_reply(user, cpy_ip, port_2);
	if (! reply)
		return (ERROR);
	send_reply(com, reply);
	user->transfert_mode = PASV;
	free(reply);
	return (SUCCESS);
}
