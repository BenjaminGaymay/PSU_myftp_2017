/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** manage_commands
*/

#include "server.h"
#include "macro.h"

t_ptr_fct *get_cmd_ptr()
{
	static t_ptr_fct commands[14] = {
		{"USER", login, HELP_USER},
		{"PASS", password, HELP_PASS},
		{"CWD", do_cwd, HELP_CWD},
		{"CDUP", cdup, HELP_CDUP},
		{"QUIT", exit_ftp, HELP_QUIT},
		{"DELE", delete_file, HELP_DEL},
		{"PWD", do_pwd, HELP_PWD},
		{"PASV", pasv, HELP_PASV},
		{"PORT", port, HELP_PORT},
		{"HELP", show_help, HELP_HELP},
		{"NOOP", noop, HELP_NOOP},
		{"STOR", receive_file, HELP_STOR},
		{"RETR", send_file, HELP_RETR},
		{"LIST", do_ls, HELP_LIST}
	};

	return (commands);

}

char *clear_command(char *cmd)
{
	if (cmd[strlen(cmd) - 1] == '\n' && cmd[strlen(cmd) - 2] == '\r')
		cmd[strlen(cmd) - 2] = '\0';
	else if (cmd[strlen(cmd) - 1] == '\n')
		cmd[strlen(cmd) - 1] = '\0';
	return (cmd);
}

int exec_command(const int com, t_user_infos *user, t_ptr_fct *fct, char *cmd)
{
	char *cmd_cpy = &cmd[strlen(fct->name) + (cmd[strlen(fct->name)] == ' ' ? 1 : 0)];
	int ret_value = fct->fct(com, cmd_cpy, user);

	free(cmd);
	return (ret_value);
}

int get_command(const int com, t_user_infos *user)
{
	size_t len = 0;
	char *cmd = NULL;
	FILE *file = fdopen(com, "r");
	t_ptr_fct fct;
	t_ptr_fct *commands = get_cmd_ptr();

	if (! file)
		return (FCT_FAIL("fdopen"), ERROR);
	getline(&cmd, &len, file);
	for (int i = 13 ; i >= 0 ; i--) {
		fct = commands[i];
		cmd = clear_command(cmd);
		if (strncasecmp(cmd, fct.name, strlen(fct.name)) == SUCCESS)
			return (exec_command(com, user, &fct, cmd));
	}
	return (send_reply(com, BAD_CMD), FAILURE);
}