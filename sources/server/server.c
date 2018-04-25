/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "server.h"
#include "macro.h"

int server_loop(const int serv, const int port, char *root)
{
	struct sockaddr_in client;
	socklen_t client_size;
	int com;
	pid_t pid;

	while (1) {
		client_size = sizeof(client);
		com = accept(serv, (struct sockaddr *)&client, &client_size);
		pid = fork();
		if (pid == -1)
			return (FCT_FAIL("fork"), safe_close(com, ERROR));
		if (pid != 0)
			printf("[*] New connection from %s:%d\n",
				inet_ntoa(client.sin_addr),
				ntohs(client.sin_port));
		else
			return (one_client_loop(com, &client, port, root));
		close(com);
	}
	return (SUCCESS);
}

int main(const int ac, const char **av)
{
	int serv;
	char *path;

	if (check_help(av) == SUCCESS)
		return (SUCCESS);
	if (ac != 3)
		return (print_usage(ERROR));
	path = realpath(av[2], NULL);
	if (chdir(av[2]) == -1)
		return (fprintf(stderr, "Error: %s: Bad path\n",
				av[2]), ERROR);
	srand(time(NULL));
	serv = create_socket(atoi(av[1]), INADDR_ANY, SERVER, VERBOSE);
	if (serv == FD_ERROR || server_loop(serv, atoi(av[1]), path) == ERROR)
		return (free(path), safe_close(serv, ERROR));
	free(path);
	return (safe_close(serv, SUCCESS));
}