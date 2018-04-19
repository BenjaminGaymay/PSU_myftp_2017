/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "client.h"
#include "macro.h"

int is_reply_end(const char *line)
{
	for (int i = 0 ; line[i] && i < 3 ; i++)
		if (isdigit(line[i]) == 0)
			return (FAILURE);
	return (SUCCESS);
}

int wait_reply(const int com, char **reply)
{
	size_t len = 0;
	char *line = NULL;
	FILE *file = fdopen(com, "r");

	if (! file)
		return (FCT_FAIL("fdopen"), ERROR);
	while (getline(&line, &len, file) && is_reply_end(line) == FAILURE) {
		if (line[0] != '\n')
			write(1, line, strlen(line));
	}

	write(1, line, strlen(line));
	if (line[3] == ' ') {
		*reply = strdup(line);
		line[3] = '\0';
		return (atoi(line));
	}
	return (ERROR);

}

int client_loop(const int com)
{
	char *cmd;
	char *reply;
	int reply_state;
	t_data_transfert_info infos;

	infos.com = com;
	reply_state = wait_reply(com, &reply);
	if (reply_state == ERROR || reply_state == 421)
		return (ERROR);
	free(reply);
	while (1) {
		cmd = get_command(com);
		if (cmd == NULL)
			return (ERROR);
		reply_state = wait_reply(com, &reply);
		if (reply_state == 221 || reply_state == ERROR)
			return (reply_state);
		else if (reply_state == FAILURE)
			fprintf(stderr, "Error: %s: bad command\n", cmd);
		else if (reply_state != 421 && make_command(cmd, reply, &infos) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
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