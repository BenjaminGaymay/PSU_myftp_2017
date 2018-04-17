/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** help
*/

#include <stdio.h>
#include <string.h>
#include "macro.h"

int print_usage(int ret_value)
{
	printf("%s\n", "USAGE: ./server port path\n\tport is the port " \
			"number on which the server socket listens\n\t" \
			"path is the path to the home directory for th" \
			"e Anonymous user");
	return (ret_value);
}

int check_help(const char **av)
{
	for (int i = 1 ; av[i] ; i++) {
		if (strcmp(av[i], "-h") == SUCCESS ||
			strcmp(av[i], "--h") == SUCCESS ||
			strcmp(av[i], "-help") == SUCCESS ||
			strcmp(av[i], "--help") == SUCCESS)
				return (print_usage(SUCCESS));
	}
	return (FAILURE);
}
