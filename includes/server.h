/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** server
*/

#pragma once

#include "socket.h"

typedef struct s_user_infos {
	char *server_ip;
	char *client_ip;
	int server_port;
	int user_port;
	int datas_transfert_port;
	char *login;
	int connected;
	int data_transfert_socket;
} t_user_infos;

typedef struct s_ptr_fct {
	char *name;
	int (*fct)(const int, char *, t_user_infos *);
	char *help;
} t_ptr_fct;

int check_help(const char **);
int print_usage(int);

t_ptr_fct *get_cmd_ptr();
void send_reply(const int, const char *);
int get_command(const int, t_user_infos *);

int login(const int, char *, t_user_infos *);
int password(const int, char *, t_user_infos *);
int do_cwd(const int, char *, t_user_infos *);
int cdup(const int, char *, t_user_infos *);
int exit_ftp(const int, char *, t_user_infos *);
int delete_file(const int, char *, t_user_infos *);
int do_pwd(const int, char *, t_user_infos *);
int port(const int, char *, t_user_infos *);
int pasv(const int, char *, t_user_infos *);
int show_help(const int, char*, t_user_infos *);
int noop(const int, char *, t_user_infos *);
int receive_file(const int, char *, t_user_infos *);
int send_file(const int, char *, t_user_infos *);
int do_ls(const int, char *, t_user_infos *);
