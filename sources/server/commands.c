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
	if (user->login != NULL)
		free(user->login);
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
	else if (user->connected == CONNECT)
		return (send_reply(com, ALREADY_CONNECTED), FAILURE);
	if (strcmp(user->login, "Anonymous") != SUCCESS)
		return (user->connected = LOGIN,
			send_reply(com, BAD_LOG), FAILURE);
	if (strcmp(pass, "") != SUCCESS)
		return (send_reply(com, BAD_PASS), FAILURE);
	user->connected = CONNECT;
	return (send_reply(com, CONNECTED), SUCCESS);
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
	if (access(file, W_OK) == 0 && remove(file) == 0)
		send_reply(com, FILE_OKAY);
	else
		send_reply(com, FILE_UNWRITABLE);
	return (SUCCESS);
}
