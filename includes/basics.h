/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** basics
*/

#pragma once

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>

char *replace_char(char *, const char, const char);
int read_file(const char *, const int);