/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** macro
*/

#pragma once

#define SUCCESS 0
#define FAILURE 1
#define ERROR 84
#define EXIT -1
#define FD_ERROR -1

#define LOGIN -1
#define CONNECT 0
#define PASSWORD 1

#define FCT_FAIL(name) fprintf(stderr, "Error: %s failed\n", name)

#define CONNECT_OPEN "150 File status okay; about to open data connection."
#define CMD_OKAY "200 Command okay."
#define HELP "214 Help message."
#define READY "220 Service ready for new user."
#define LOGOUT "221 Service closing control connection."
#define CLOSE_CONNECTION "226 Closing data connection."
#define PASSIVE "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)."
#define CONNECTED "230 User logged in, proceed."
#define FILE_OKAY "250 Requested file action okay, completed."
#define GOOD_LOGIN "331 User name okay, need password."
#define NEED_ACC "332 Need account for login."
#define BAD_CMD "421 Bad command."
#define BAD_LOG "421 Bad login."
#define BAD_PASS "421 Bad password."
#define BAD_PATH "421 Bad path."
#define ALREADY_CONNECTED "421 Already connected."
#define NOT_CONNECTED "421 You are not connected."

#define HELP_USER "USER <SP> <username> <CRLF>   : Specify user for authentication\n"
#define HELP_PASS "PASS <SP> <password> <CRLF>   : Specify password for authentication\n"
#define HELP_CWD "CWD  <SP> <pathname> <CRLF>   : Change working directory\n"
#define HELP_CDUP "CDUP <CRLF>                   : Change working directory to parent directory\n"
#define HELP_QUIT "QUIT <CRLF>                   : Disconnection\n"
#define HELP_DEL "DELE <SP> <pathname> <CRLF>   : Delete file on the server\n"
#define HELP_PWD "PWD  <CRLF>                   : Print working directory\n"
#define HELP_PASV "PASV <CRLF>                   : Enable \"passive\" mode for data transfer\n"
#define HELP_PORT "PORT <SP> <host-port> <CRLF>  : Enable \"active\" mode for data transfer\n"
#define HELP_HELP "HELP [<SP> <string>] <CRLF>   : List available commands\n"
#define HELP_NOOP "NOOP <CRLF>                   : Do nothing\n"
#define HELP_DATA "(the following are commands using data transfer)\n"
#define HELP_RETR "RETR <SP> <pathname> <CRLF>   : Download file from server to client\n"
#define HELP_STOR "STOR <SP> <pathname> <CRLF>   : Upload file from client to server\n"
#define HELP_LIST "LIST [<SP> <pathname>] <CRLF> : List files in the current working directory\n"
