/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "server.h"
#include "macro.h"

void send_reply(const int com, const char *msg)
{
	write(com, msg, strlen(msg));
	if (msg[strlen(msg)] != '\n')
		write(com, "\n", 1);
}

char *get_host_ip(const int com)
{
	struct sockaddr_in server;
	int server_size;

	server_size = sizeof(server);
	if (getsockname(com, &server, (socklen_t *)&server_size) == FD_ERROR)
		return (FCT_FAIL("getsockname"), NULL);
	return (inet_ntoa(server.sin_addr));
}

t_user_infos fill_user_infos(const struct sockaddr_in *client,
		int port, char *root)
{
	t_user_infos new_user = {
		root,
		NULL,
		inet_ntoa(client->sin_addr),
		port,
		ntohs(client->sin_port),
		FD_ERROR,
		NULL,
		LOGIN,
		FD_ERROR,
		NONE
	};

	return (new_user);
}

int one_client_loop(const int com, const struct sockaddr_in *client,
		int port, char *root)
{
	int state;
	t_user_infos new_user = fill_user_infos(client, port, root);

	if (com == FD_ERROR)
		return (FCT_FAIL("accept"), ERROR);
	new_user.server_ip = get_host_ip(com);
	if (new_user.server_ip == NULL)
		return (ERROR);
	send_reply(com, READY);
	while (1) {
		state = get_command(com, &new_user);
		if (state == ERROR)
			return (ERROR);
		else if (state == EXIT)
			return (printf("[*] Client from %s:%d exited\n",
					new_user.client_ip,
					new_user.client_port),
				SUCCESS);
	}
	return (SUCCESS);
}

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
		if (pid == 0)
			printf("[*] New connection from %s:%d\n",
				inet_ntoa(client.sin_addr),
				ntohs(client.sin_port));
		else
			return (one_client_loop(com, &client, port, root));

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
		return (safe_close(serv, ERROR));
	return (safe_close(serv, SUCCESS));
}