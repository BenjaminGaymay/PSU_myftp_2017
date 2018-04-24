/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** commands
*/

#include "client.h"
#include "macro.h"

int pasv(char *cmd, char *reply, t_data_transfert_info *infos)
{
	int port_2 = get_port_from_cmd(reply, 1);
	int port_1 = get_port_from_cmd(reply, 0);

	(void)cmd;
	close(infos->serv_mode);
	infos->port = port_1 * 256 + port_2;
	if (infos->ip != NULL)
		free(infos->ip);
	infos->ip = strdup(get_ip_from_cmd(reply));
	if (! infos->ip)
		return (FCT_FAIL("strdup"), ERROR);
	infos->transfert_mode = PASV;
	free(reply);
	return (SUCCESS);
}

int port(char *cmd, char *reply, t_data_transfert_info *infos)
{
	int port_2 = get_port_from_cmd(cmd, 1);
	int port_1 = get_port_from_cmd(cmd, 0);

	(void)reply;
	close(infos->serv_mode);
	infos->port = port_1 * 256 + port_2;
	infos->serv_mode = create_socket(infos->port,
		INADDR_ANY, SERVER, VERBOSE);
	if (infos->serv_mode == FD_ERROR)
		return (ERROR);
	infos->transfert_mode = PORT;
	free(reply);
	return (SUCCESS);
}