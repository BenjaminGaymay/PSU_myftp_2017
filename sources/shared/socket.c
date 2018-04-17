/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "socket.h"
#include "macro.h"

int safe_close(const int fd, const int ret)
{
	if (close(fd) == -1)
		return (fprintf(stderr, "Error: close failed\n"), ERROR);
	return (ret);
}

int s_socket(int fd, struct sockaddr_in *s_in)
{
	if (bind(fd, (const struct sockaddr *)s_in, sizeof(*s_in)) == -1)
		return (FCT_FAIL("bind"), safe_close(fd, FD_ERROR));
	if (listen(fd, 42) == -1)
		return (FCT_FAIL("listen"), safe_close(fd, FD_ERROR));
	return (fd);
}

int c_socket(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1)
		return (FCT_FAIL("connect"), safe_close(fd, FD_ERROR));
	return (fd);
}

int create_socket(const int port, const in_addr_t addr, e_socket_type s_t)
{
	int fd;
	struct protoent *pe;
	struct sockaddr_in s_in;

	pe = getprotobyname("TCP");
	if (! pe)
		return (FCT_FAIL("getprotobyname"), FD_ERROR);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return (FCT_FAIL("socket"), FD_ERROR);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = addr;
	return (s_t == SERVER ? s_socket(fd, &s_in) : c_socket(fd, &s_in));
}