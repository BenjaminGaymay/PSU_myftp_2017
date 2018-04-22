##
## EPITECH PROJECT, 2018
## PSU_myftp_2017
## File description:
## Makefile
##

NAME_SERVER	= server
NAME_CLIENT	= my_ftp

CC	= gcc

RM	= rm -f

SRCS_CLIENT	= ./sources/client/client.c		\
		  ./sources/client/manage_reply.c	\
		  ./sources/client/ptr_fct.c		\
		  ./sources/client/manage_commands.c	\
		  ./sources/client/send_file.c		\
		  ./sources/client/commands.c		\
		  ./sources/client/local_commands.c	\
		  ./sources/shared/basics.c		\
		  ./sources/shared/socket.c

SRCS_SERVER	= ./sources/server/server.c		\
		  ./sources/server/manage_commands.c	\
		  ./sources/server/commands.c		\
		  ./sources/server/help.c		\
		  ./sources/server/transfert_data.c	\
		  ./sources/server/connection_mode.c	\
		  ./sources/server/basics_cmd.c		\
		  ./sources/shared/basics.c		\
		  ./sources/shared/socket.c

OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

CFLAGS = -I ./includes/
CFLAGS += -W -Wall -Wextra

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	 $(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

$(NAME_SERVER): $(OBJS_SERVER)
	 $(CC) $(OBJS_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

clean:
	$(RM) $(OBJS_CLIENT)
	$(RM) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
