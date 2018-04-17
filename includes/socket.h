/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

typedef enum {
	CLIENT,
	SERVER
} e_socket_type;

int safe_close(const int, const int);
int create_socket(const int, const in_addr_t, e_socket_type s_t);