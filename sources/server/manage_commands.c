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
	static t_ptr_fct commands[19] = {
		{"USER", login, HELP_USER},
		{"PASS", password, HELP_PASS},
		{"CWD", do_cwd, HELP_CWD},
		{"cd", do_cwd, ""},
		{"CDUP", cdup, HELP_CDUP},
		{"QUIT", exit_ftp, HELP_QUIT},
		{"DELE", delete_file, HELP_DEL},
		{"PWD", do_pwd, HELP_PWD},
		{"pwd", do_pwd, ""},
		{"PASV", pasv, HELP_PASV},
		{"PORT", port, HELP_PORT},
		{"HELP", show_help, HELP_HELP},
		{"NOOP", noop, HELP_NOOP},
		{"STOR", receive_file, HELP_STOR},
		{"put", receive_file, ""},
		{"RETR", send_file, HELP_RETR},
		{"get", send_file, ""},
		{"LIST", do_ls, HELP_LIST},
		{"ls", do_ls, ""}
	};

	return (commands);

}

int get_command(const int com, int *connected)
{
	size_t len = 0;
	char *line = NULL;
	char *cpy;
	FILE *file = fdopen(com, "r");
	int ret_value = FAILURE;
	t_ptr_fct tmp;
	t_ptr_fct *commands = get_cmd_ptr();

	if (! file)
		return (FCT_FAIL("fdopen"), ERROR);
	getline(&line, &len, file);
	for (int i = 18 ; i >= 0 ; i--) {
		tmp = commands[i];
		if (line[strlen(line) - 1] == '\n' && line[strlen(line) - 2] == '\r')
			line[strlen(line) - 2] = '\0';
		if (strncmp(line, tmp.name, strlen(tmp.name)) == SUCCESS) {
			cpy = &line[strlen(tmp.name) + (line[strlen(tmp.name)] == ' ' ? 1 : 0)];
			ret_value = tmp.fct(com, cpy, connected);
			return (free(line), ret_value);
		}
	}
	return (send_reply(com, BAD_CMD), FAILURE);
}