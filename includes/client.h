/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** client
*/

#pragma once

#include "socket.h"

typedef struct s_data_transfert_info {
	char *ip;
	int port;
	int com;
	int data_transfert;
	int serv_mode;
	e_transfert_mode transfert_mode;
} t_data_transfert_info;

typedef struct s_ptr_fct_serv {
	char *name;
	int (*fct)(char *, char *, t_data_transfert_info *);
} t_ptr_fct_serv;

typedef struct s_ptr_fct_cli {
	char *name;
	int (*fct)(char *);
} t_ptr_fct_cli;

int server_open(const int);
int wait_reply(const int, char **);

t_ptr_fct_cli *get_client_commands();
t_ptr_fct_serv *get_server_commands();

char *get_command();
int make_command(const int, char *, t_data_transfert_info *);
int exec_client_command(char *);
int send_file(char *, char *, t_data_transfert_info *);
int receive_file(char *, char *, t_data_transfert_info *);
int receive_cmd(char *, char *, t_data_transfert_info *);
int pasv(char *, char *, t_data_transfert_info *);
int port(char *, char *, t_data_transfert_info *);

int is_client_cmd(char *);
int do_pwd(char *);
int do_cwd(char *);
int do_ls(char *);