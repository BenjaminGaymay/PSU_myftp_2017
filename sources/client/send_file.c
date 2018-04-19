/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** send_file
*/

#include "client.h"
#include "macro.h"

void connect_data_transfert_socket(t_data_transfert_info *infos)
{
	infos->data_transfert = create_socket(infos->port_1, inet_addr(infos->ip), CLIENT);
}

int receive_cmd(char *cmd, char *reply, t_data_transfert_info *infos)
{
	char *line = NULL;

	(void)cmd;
	(void)reply;
	connect_data_transfert_socket(infos);
	read_file(NULL, infos->data_transfert);
	wait_reply(infos->com, &line);
	return (free(line), SUCCESS);
}

int send_file(char *cmd, char *reply, t_data_transfert_info *infos)
{
	char *tmp;
	char *path = strndup(&cmd[5], strlen(&cmd[5]));

	(void)reply;
	connect_data_transfert_socket(infos);
	if (! path)
		return (FCT_FAIL("strndup"), ERROR);
	if (access(path, F_OK) == -1) {
		close (infos->data_transfert);
		fprintf(stderr, "Error: file '%s' doesn't exist\n", path);
		wait_reply(infos->com, &tmp);
		return (free(path), free(tmp), FAILURE);
	}
	if (infos->data_transfert == FD_ERROR)
		return (ERROR);
	read_file(path, infos->data_transfert);
	close(infos->data_transfert);
	wait_reply(infos->com, &tmp);
	infos->data_transfert = FD_ERROR;
	return (free(tmp), free(path), SUCCESS);
}
