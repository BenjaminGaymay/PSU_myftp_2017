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

int one_client_loop(const int com, const struct sockaddr_in *client, const int port)
{
	int state;
	t_user_infos new_user = {
		inet_ntoa(client->sin_addr),
		port,
		ntohs(client->sin_port),
		NULL,
		LOGIN,
		FD_ERROR
	};

	if (com == -1)
		return (FCT_FAIL("accept"), ERROR);
	send_reply(com, READY);
	while (1) {
		state = get_command(com, &new_user);
		if (state == ERROR)
			return (ERROR);
		else if (state == EXIT)
			return (printf("[*] Client from %s:%d exited\n",
					new_user.ip, new_user.user_port),
					SUCCESS);
	}
	return (SUCCESS);
}

int server_loop(const int serv, const int port)
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
		else {
			if (one_client_loop(com, &client, port) == ERROR)
				return (safe_close(com, ERROR));
			break;
		}

	}
	return (SUCCESS);
}

int main(const int ac, const char **av)
{
	int serv;

	if (check_help(av) == SUCCESS)
		return (SUCCESS);
	if (ac != 3)
		return (print_usage(ERROR));
	if (chdir(av[2]) == -1)
		return (fprintf(stderr, "Error: %s: Bad path\n", av[2]), ERROR);
	serv = create_socket(atoi(av[1]), INADDR_ANY, SERVER);
	if (serv == FD_ERROR || server_loop(serv, atoi(av[1])) == ERROR)
		return (safe_close(serv, ERROR));
	return (safe_close(serv, SUCCESS));
}