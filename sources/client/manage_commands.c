/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** manage_commands
*/

#include "client.h"
#include "macro.h"

static int send_command(const int com, char *cmd)
{
	char *tmp;

	asprintf(&tmp, "%s\r\n", cmd);
	if (! tmp)
		return (FCT_FAIL("asprintf"), ERROR);
	if (server_open(com) == ERROR)
		return (ERROR);
	write(com, tmp, strlen(tmp));
	free(tmp);
	return (SUCCESS);
}

static int communicate_with_server(const int com, char *cmd, char **reply)
{

	if (send_command(com, cmd) == ERROR)
		return (ERROR);
	return (wait_reply(com, reply));
}

char *get_command(void)
{
	size_t len = 0;
	char *line = NULL;

	printf(" > ");
	getline(&line, &len, stdin);
	line[strlen(line) - 1] = '\0';
	return (line);
}

int make_command(const int com, char *cmd, t_data_transfert_info *infos)
{
	char *reply;
	t_ptr_fct_serv tmp;
	t_ptr_fct_serv *commands_server = get_server_commands();
	int reply_state = communicate_with_server(com, cmd, &reply);
	int errors[5] = {ERROR, 221, 421, 500, 530};

	for (int i = 0 ; i < 5 ; i++)
		if (errors[i] == reply_state)
			return (free(reply), reply_state);
	for (int i = 0 ; i < 7 ; i++) {
		tmp = commands_server[i];
		if (strncasecmp(tmp.name, cmd, strlen(tmp.name)) == SUCCESS)
			return (tmp.fct(&cmd[strlen(tmp.name) + 1],
				reply, infos));
	}
	free(reply);
	return (FAILURE);
}

int exec_client_command(char *cmd)
{
	t_ptr_fct_cli tmp;
	t_ptr_fct_cli *commands_client = get_client_commands();

	for (int i = 0 ; i < 3 ; i++) {
		tmp = commands_client[i];
		if (strncmp(tmp.name, cmd, strlen(tmp.name)) == SUCCESS)
			return (tmp.fct(&cmd[strlen(tmp.name) + 1]));
	}
	return (FAILURE);
}