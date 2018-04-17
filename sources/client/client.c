/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "client.h"
#include "macro.h"

int wait_reply(const int com)
{
	size_t len = 0;
	char *line = NULL;
	FILE *file = fdopen(com, "r");

	if (! file)
		return (FCT_FAIL("fdopen"), ERROR);
	getline(&line, &len, file);
	write(1, line, strlen(line));
	for (int i = 0 ; line[i] && i < 3 ; i++)
		if (isdigit(line[i]) == 0)
			return (ERROR);
	if (line[3] == ' ') {
		line[3] = '\0';
		return (atoi(line));
	}
	return (ERROR);

}

int client_loop(const int com)
{
	char *cmd;
	int reply_state;

	reply_state = wait_reply(com);
	if (reply_state == ERROR || reply_state == 421)
		return (ERROR);
	while (1) {
		cmd = get_command(com);
		if (cmd == NULL)
			return (ERROR);
		reply_state = wait_reply(com);
		if (reply_state == 221 || reply_state == ERROR)
			return (reply_state);
		else if (reply_state == FAILURE)
			fprintf(stderr, "Error: %s: bad command\n", cmd);
		else if (make_command(com, cmd) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int main(const int ac, char **av)
{
	int com;

	if (ac != 3)
		return (ERROR);
	com = create_socket(atoi(av[2]), inet_addr(av[1]), CLIENT);
	if (com == FD_ERROR || client_loop(com) == ERROR)
		return (safe_close(com, ERROR));
	return (safe_close(com, SUCCESS));
}