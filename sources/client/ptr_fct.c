/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ptr_fct
*/

#include "client.h"

t_ptr_fct_serv *get_server_commands(void)
{
	static t_ptr_fct_serv commands_server[7] = {
		{"STOR", send_file},
		{"put", send_file},
		{"RETR", receive_file},
		{"get", receive_file},
		{"LIST", receive_cmd},
		{"PASV", pasv},
		{"PORT", port}
	};

	return (commands_server);
}

t_ptr_fct_cli *get_client_commands(void)
{
	static t_ptr_fct_cli commands_client[3] = {
		{"ls", do_ls},
		{"cd ", do_cwd},
		{"pwd", do_pwd}
	};

	return (commands_client);
}