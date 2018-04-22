/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** basics_cmd
*/

#include "server.h"
#include "macro.h"

int do_pwd(const int com, char *cmd, t_user_infos *user)
{
	char *reply;

	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	asprintf(&reply, "257 \"%s\"\n", getcwd(NULL, 0));
	if (! reply)
		return (FCT_FAIL("asprintf"), ERROR);
	send_reply(com, reply);
	free(reply);
	return (SUCCESS);
}

int do_cwd(const int com, char *cmd, t_user_infos *user)
{
	char *old_pwd = getcwd(NULL, 0);

	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir(cmd) == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	if (strncmp(user->root, getcwd(NULL, 0), strlen(user->root)) == 0)
		return (send_reply(com, FILE_OKAY), SUCCESS);
	chdir(old_pwd);
	return (send_reply(com, PERM_DENIED), FAILURE);
}

int cdup(const int com, char *cmd, t_user_infos *user)
{
	char *old_pwd = getcwd(NULL, 0);

	(void)cmd;
	if (user->connected != CONNECT)
		return (send_reply(com, NOT_CONNECTED), FAILURE);
	if (chdir("..") == -1)
		return (send_reply(com, BAD_PATH), FAILURE);
	if (strncmp(user->root, getcwd(NULL, 0), strlen(user->root)) == 0)
		return (send_reply(com, FILE_OKAY), SUCCESS);
	chdir(old_pwd);
	return (send_reply(com, PERM_DENIED), FAILURE);
}

int noop(const int com, char *cmd, t_user_infos *user)
{
	(void)cmd;
	(void)user;
	send_reply(com, CMD_OKAY);
	return (SUCCESS);
}

int show_help(const int com, char *cmd, t_user_infos *user)
{
	t_ptr_fct tmp;
	t_ptr_fct *commands = get_cmd_ptr();

	(void)user;
	for (int i = 0 ; i < 14 ; i++) {
		tmp = commands[i];
		if (cmd[0] == '\0' && i == 11)
			send_reply(com, HELP_DATA);
		if (cmd[0] == '\0' || strncasecmp(cmd, tmp.name, strlen(tmp.name)) == SUCCESS)
			send_reply(com, tmp.help);
	}
	send_reply(com, HELP);
	return (SUCCESS);
}