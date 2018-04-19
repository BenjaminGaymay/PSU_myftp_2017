/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** manage_commands
*/

#include "client.h"
#include "macro.h"

t_ptr_fct commands[7] = {
	{"STOR", send_file},
	{"put", send_file},
	{"RETR", receive_cmd},
	{"get", receive_cmd},
	{"LIST", receive_cmd},
	{"ls", receive_cmd},
	{"PASV", pasv}

};

int send_command(const int com, char *cmd)
{
	char *tmp;

	asprintf(&tmp, "%s\r\n", cmd);
	if (! tmp)
		return (FCT_FAIL("asprintf"), ERROR);
	write(com, tmp, strlen(tmp));
	free(tmp);
	return (SUCCESS);
}

char *get_command(const int com)
{
	size_t len = 0;
	char *line = NULL;

	printf(" > ");
	getline(&line, &len, stdin);
	line[strlen(line) - 1] = '\0';
	if (send_command(com, line) == ERROR)
		return (NULL);
	return (line);
}

int make_command(char *cmd, char *reply, t_data_transfert_info *infos)
{
	t_ptr_fct tmp;

	for (int i = 0 ; i < 7 ; i++) {
		tmp = commands[i];
		if (strncmp(cmd, tmp.name, strlen(tmp.name)) == SUCCESS)
			return (tmp.fct(cmd, reply, infos));
	}
	free(reply);
	return (FAILURE);
}