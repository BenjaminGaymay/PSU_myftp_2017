/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** send_file
*/

#include "client.h"
#include "macro.h"

int connect_data_transfert_socket(t_data_transfert_info *infos)
{
	struct sockaddr_in server;
	socklen_t server_size;

	server_size = sizeof(server);
	if (infos->transfert_mode == PORT) {
		infos->data_transfert = accept(infos->serv_mode, (struct sockaddr *)&server, &server_size);
		return (SUCCESS);
	}
	infos->data_transfert = create_socket(infos->port, inet_addr(infos->ip), CLIENT, VERBOSE);
	return (infos->data_transfert == FD_ERROR ? ERROR : SUCCESS);
}

int receive_cmd(char *cmd, char *reply, t_data_transfert_info *infos)
{
	char *line = NULL;

	(void)cmd;
	(void)reply;
	if (connect_data_transfert_socket(infos) == ERROR)
		return (ERROR);
	read_file(NULL, infos->data_transfert);
	wait_reply(infos->com, &line);
	return (free(line), SUCCESS);
}

int receive_file(char *cmd, char *reply, t_data_transfert_info *infos)
{
	char *line = NULL;

	(void)cmd;
	(void)reply;
	if (connect_data_transfert_socket(infos) == ERROR)
		return (ERROR);
	create_file(cmd, infos->data_transfert);
	wait_reply(infos->com, &line);
	return (free(line), SUCCESS);
}

int send_file(char *cmd, char *reply, t_data_transfert_info *infos)
{
	char *tmp;
	char *path = strndup(cmd, strlen(cmd));

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
