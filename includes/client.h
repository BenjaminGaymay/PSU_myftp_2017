/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** client
*/

#pragma once

#define _GNU_SOURCE
#include <ctype.h>
#include "socket.h"

typedef struct s_ptr_fct {
	char *name;
	int (*fct)(const int, char *);
} t_ptr_fct;

char *get_command(const int);
int make_command(const int, char *);
int send_file(const int, char *);
int receive_cmd(const int, char *);
int receive_cmd(const int, char *);
