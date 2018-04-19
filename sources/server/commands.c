/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** commands
*/

#include "server.h"
#include "macro.h"

int login(const int com, char *login, t_user_infos *user)
{
	user->login = strdup(login);
	if (! user->login)
		return (FCT_FAIL("strdup"), ERROR);
	user->connected = PASSWORD;
	return (send_reply(com, GOOD_LOGIN), SUCCESS);
}

int password(const int com, char *pass, t_user_infos *user)
{

	if (user->connected == LOGIN || ! user->login)
		return (send_reply(com, NEED_ACC), FAILURE);
	if (strcmp(user->login, "Anonymous") != SUCCESS)
		return (user->connected = LOGIN, send_reply(com, BAD_LOG), FAILURE);
	if (strcmp(pass, "") != SUCCESS)
		return (send_reply(com, BAD_PASS), FAILURE);
	else if (user->connected == CONNECT)
		return (send_reply(com, ALREADY_CONNECTED), FAILURE);
	user->connected = CONNECT;
	return (send_reply(com, CONNECTED), SUCCESS);
}

int do_cwd(const int com, char *cmd, t_user_infos *user)
{
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir(cmd) == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	send_reply(com, FILE_OKAY);
	return (SUCCESS);
}

int cdup(const int com, char *cmd, t_user_infos *user)
{
	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir("..") == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int exit_ftp(const int com, char *cmd, t_user_infos *user)
{
	(void)cmd;
	user->connected = FAILURE;
	send_reply(com, LOGOUT);
	return (safe_close(com, EXIT));
}

int delete_file(const int com, char *file, t_user_infos *user)
{
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	remove(file);
	send_reply(com, FILE_OKAY);
	return (SUCCESS);
}

int do_pwd(const int com, char *cmd, t_user_infos *user)
{
	FILE *stream;
	char *path = NULL;
	char *reply;
	size_t len = 0;

	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);

	stream = popen("pwd", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	getline(&path, &len, stream);
	path[strlen(path) - 1] = '\0';
	asprintf(&reply, "257 \"%s\"\n", path);
	if (! reply)
		return (FCT_FAIL("asprintf"), ERROR);
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	send_reply(com, reply);
	free(reply);
	free(path);
	return (SUCCESS);
}

int port(const int com, char *cmd, t_user_infos *user)
{
	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	printf(" ~ Active mode enable for datas transfert\n");
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int port_is_free(const int port_1, const int port_2)
{
	struct sockaddr_in sin;
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == FD_ERROR)
  		return (FCT_FAIL("socket"), ERROR);

	sin.sin_port = htons(port_1 * 256 + port_2);
	sin.sin_addr.s_addr = 0;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;

	if (bind(fd, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == FD_ERROR)
  		return (close(fd), FAILURE);
  	return (close(fd), SUCCESS);
}

int pasv(const int com, char *cpy_ip, t_user_infos *user)
{
	char *reply;
	int port_1;
	int port_2;

	close(user->data_transfert_socket);
	user->data_transfert_socket = FD_ERROR;
	while (user->data_transfert_socket == FD_ERROR) {
		port_1 = rand() % 256;
		port_2 = rand() % 256;
		user->datas_transfert_port = port_1 * 256 + port_2;
		user->data_transfert_socket = create_socket(user->datas_transfert_port, INADDR_ANY, SERVER, QUIET);
	}
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	printf(" ~ Passive mode enable for datas transfert\n");
	cpy_ip = strdup(user->server_ip);
	if (! cpy_ip)
		return (FCT_FAIL("strdup"), ERROR);
	asprintf(&reply, "227 Entering Passive Mode (%s,%d,%d).\n", replace_char(cpy_ip, '.', ','), port_1 , port_2);
	if (! reply)
		return (FCT_FAIL("asprintf"), ERROR);
	send_reply(com, reply);
	free(reply);
	return (SUCCESS);
}

int show_help(const int com, char *cmd, t_user_infos *user)
{
	t_ptr_fct tmp;
	t_ptr_fct *commands = get_cmd_ptr();

	(void)user;
	for (int i = 0 ; i < 19 ; i++) {
		tmp = commands[i];
		if (cmd[0] == '\0' && i == 13)
			send_reply(com, HELP_DATA);
		if (cmd[0] == '\0' || strncmp(cmd, tmp.name, strlen(tmp.name)) == SUCCESS)
			send_reply(com, tmp.help);
	}

	send_reply(com, HELP);
	return (SUCCESS);
}

int noop(const int com, char *cmd, t_user_infos *user)
{
	(void)cmd;
	(void)user;
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int get_data_transfert_socket(t_user_infos *user)
{
	struct sockaddr_in client;
	socklen_t client_size;

	client_size = sizeof(client);
	return (accept(user->data_transfert_socket, (struct sockaddr *)&client, &client_size));
}

int receive_file(const int com, char *cmd, t_user_infos *user)
{
	int socket;

	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (user->data_transfert_socket == FD_ERROR)
		return (send_reply(com, REQUEST_PORT), FAILURE);
	send_reply(com, CONNECT_OPEN);

	socket = get_data_transfert_socket(user);
	printf(" > Client %s connected with datas transfert socket on port %d\n", user->server_ip, user->datas_transfert_port);
	read_file(NULL, socket);
	printf(" ~ File \"%s\" received from %s on port %d\n", cmd, user->server_ip, user->datas_transfert_port);
	send_reply(com, CLOSE_CONNECTION);
	printf(" < Data transfert socket closed for %s on port %d\n", user->server_ip, user->datas_transfert_port);
	return (SUCCESS);
}

int send_file(const int com, char *cmd, t_user_infos *user)
{
	int socket;

	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (user->data_transfert_socket == FD_ERROR)
		return (send_reply(com, REQUEST_PORT), FAILURE);
	send_reply(com, CONNECT_OPEN);

	socket = get_data_transfert_socket(user);
	printf(" > Client %s connected with datas transfert socket on port %d\n", user->server_ip, user->datas_transfert_port);
	if (access(cmd, F_OK) == -1) {
		close (socket);
		send_reply(com, FILE_NOT_EXIST);
		return (FAILURE);
	}
	read_file(cmd, socket);
	printf(" ~ File \"%s\" sent to %s on port %d\n", cmd, user->server_ip, user->datas_transfert_port);
	close (socket);
	send_reply(com, CLOSE_CONNECTION);
	printf(" < Data transfert socket closed for %s on port %d\n", user->server_ip, user->datas_transfert_port);
	return (SUCCESS);
}

int do_ls(const int com, char *cmd, t_user_infos *user)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	int socket;

	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (user->data_transfert_socket == FD_ERROR)
		return (send_reply(com, REQUEST_PORT), FAILURE);

	send_reply(com, CONNECT_OPEN);
	socket = get_data_transfert_socket(user);
	printf(" > Client %s connected with datas transfert socket on port %d\n", user->server_ip, user->datas_transfert_port);

	stream = popen("ls --color", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	while (getline(&line, &len, stream) != -1)
		write(socket, line, strlen(line));
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	close(socket);
	printf(" ~ List from current directory sent to %s on port %d\n", user->server_ip, user->datas_transfert_port);
	send_reply(com, CLOSE_CONNECTION);
	printf(" < Data transfert socket closed for %s on port %d\n", user->server_ip, user->datas_transfert_port);
	return (SUCCESS);
}