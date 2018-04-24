/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "client.h"
#include "macro.h"

static int is_connect(const int com)
{
	char *reply;
	int reply_state;

	reply_state = wait_reply(com, &reply);
	free(reply);
	if (reply_state == ERROR || reply_state == 421)
		return (FAILURE);
	return (ERROR);
}

static t_data_transfert_info init_datas_transfert(const int com)
{
	t_data_transfert_info infos = {
		NULL,
		0,
		com,
		FD_ERROR,
		FD_ERROR,
		NONE
	};

	return (infos);
}

static int launch_cmd(const int com, t_data_transfert_info *infos)
{
	char *cmd;

	cmd = get_command();
	if (cmd == NULL)
		return (ERROR);
	if (is_client_cmd(cmd) == SUCCESS && exec_client_command(cmd) == ERROR)
		return (ERROR);
	else if (is_client_cmd(cmd) != SUCCESS) {
		switch (make_command(com, cmd, infos)) {
			case ERROR:
				return (ERROR);
			case 221:
				return (free(cmd), EXIT);
		}
	}
	free(cmd);
	return (SUCCESS);
}

static int client_loop(const int com)
{
	t_data_transfert_info infos = init_datas_transfert(com);

	if (is_connect(com) == FAILURE)
		return (ERROR);
	while (1) {
		switch (launch_cmd(com, &infos)) {
			case ERROR:
				if (infos.ip != NULL)
					free(infos.ip);
				return (ERROR);
			case EXIT:
				if (infos.ip != NULL)
					free(infos.ip);
				return (SUCCESS);
		}
	}
}

int main(const int ac, char **av)
{
	int com;

	if (ac != 3)
		return (ERROR);
	com = create_socket(atoi(av[2]), inet_addr(av[1]), CLIENT, VERBOSE);
	if (com == FD_ERROR || client_loop(com) == ERROR)
		return (safe_close(com, ERROR));
	return (safe_close(com, SUCCESS));
}