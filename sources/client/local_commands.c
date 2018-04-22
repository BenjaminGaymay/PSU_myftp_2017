/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** local_commands
*/

#include "client.h"
#include "macro.h"

int is_client_cmd(char *cmd)
{
	t_ptr_fct_cli *commands_client = get_client_commands();
	t_ptr_fct_cli tmp;

	for (int i = 0 ; i < 3 ; i++) {
		tmp = commands_client[i];
		if (strncmp(cmd, tmp.name, strlen(tmp.name)) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}

int do_pwd(char *cmd)
{

	(void)cmd;
	printf("%s\n", getcwd(NULL, 0));
	return (SUCCESS);
}

int do_cwd(char *cmd)
{
	if (chdir(cmd) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int do_ls(char *cmd) {
	FILE *stream;
	char *line = NULL;
	size_t len = 0;

	(void)cmd;
	stream = popen("ls --color", "r");
	if (! stream)
		return (FCT_FAIL("popen"), ERROR);
	while (getline(&line, &len, stream) != -1)
		printf("%s", line);
	if (pclose(stream) == -1)
		return (FCT_FAIL("pclose"), ERROR);
	return (SUCCESS);
}