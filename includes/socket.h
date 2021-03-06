/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#pragma once

#include "basics.h"

typedef enum {
	CLIENT,
	SERVER
} e_socket_type;

typedef enum {
	NONE,
	PASV,
	PORT
} e_transfert_mode;

int safe_close(const int, const int);
int create_socket(const int, const in_addr_t, e_socket_type s_t, int);