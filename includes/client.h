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

typedef struct s_ptr_fct {
	char *name;
	int (*fct)(char *, char *, t_data_transfert_info *);
} t_ptr_fct;

int server_open(const int);
int wait_reply(const int, char **);

char *get_command(const int);
int make_command(char *, char *, t_data_transfert_info *);
int send_file(char *, char *, t_data_transfert_info *);
int receive_cmd(char *, char *, t_data_transfert_info *);
int pasv(char *, char *, t_data_transfert_info *);
int port(char *, char *, t_data_transfert_info *);
