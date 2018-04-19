/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** commands
*/

#include "client.h"
#include "macro.h"

char *get_ip_from_cmd(char *cmd)
{
	int i = 0;
	int start = 0;
	int coma = 0;

	while (cmd[start] && cmd[start] != '(')
		start += 1;
	for (i = start + 1 ; cmd[i] && coma != 4 ; i++) {
		if (cmd[i] == ',')
			coma += 1;
	}
	cmd[i - 1] = '\0';
	return (replace_char(&cmd[start + 1], ',', '.'));
}

int get_port_from_cmd(char *cmd, int pos)
{
	int i = 0;
	int start = 0;

	for (int coma = 0 ; cmd[start] && coma != 4 + pos ; start++)
		if (cmd[start] == ',')
			coma += 1;
	for (i = start + 1 ; cmd[i] ; i++)
		if (! isdigit(cmd[i]))
			break;
	cmd[i] = '\0';
	return (atoi(&cmd[start]));
}

int pasv(char *cmd, char *reply, t_data_transfert_info *infos)
{
	(void)cmd;
	infos->port_2 = get_port_from_cmd(reply, 1);
	infos->port_1 = get_port_from_cmd(reply, 0);
	infos->ip = strdup(get_ip_from_cmd(reply));
	if (! infos->ip)
		return (FCT_FAIL("strdup"), ERROR);
	return (SUCCESS);
}
