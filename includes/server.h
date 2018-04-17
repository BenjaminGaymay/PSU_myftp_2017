/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** server
*/

#pragma once

#define _GNU_SOURCE
#include "socket.h"

typedef struct s_ptr_fct {
	char *name;
	int (*fct)(const int, char *, int *);
	char *help;
} t_ptr_fct;

int check_help(const char **);
int print_usage(int);

t_ptr_fct *get_cmd_ptr();
void send_reply(const int, const char *);
int get_command(const int, int *);

int login(const int, char *, int *);
int password(const int, char *, int *);
int do_cwd(const int, char *, int *);
int cdup(const int, char *, int *);
int exit_ftp(const int, char *, int *);
int delete_file(const int, char *, int *);
int do_pwd(const int, char *, int *);
int port(const int, char *, int *);
int pasv(const int, char *, int *);
int show_help(const int, char*, int *);
int noop(const int, char *, int *);
int receive_file(const int, char *, int *);
int send_file(const int, char *, int *);
int do_ls(const int, char *, int *);
