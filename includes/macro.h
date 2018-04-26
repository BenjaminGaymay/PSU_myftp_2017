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

#define QUIET 0
#define VERBOSE 1

#define FCT_FAIL(name) fprintf(stderr, "Error: %s failed\n", name)

#define SOCKET_OPEN " > Client %s connected with datas transfert socket on port %d\n"
#define SOCKET_CLOSE " < Data transfert socket closed for %s on port %d\n"
#define RETR_LOGS "\t~ File \"%s\" sent to %s on port %d\n"
#define STOR_LOGS "\t~ File \"%s\" received from %s on port %d\n"
#define LIST_LOGS "\t~ List from current directory sent to %s on port %d\n"

#define CONNECT_OPEN "150 File status okay; about to open data connection."
#define CMD_OKAY "200 Command okay."
#define HELP "214 Help message."
#define READY "220 Service ready for new user."
#define LOGOUT "221 Service closing control connection."
#define CLOSE_CONNECTION "226 Closing data connection."
#define CONNECTED "230 User logged in, proceed."
#define FILE_OKAY "250 Requested file action okay, completed."
#define GOOD_LOGIN "331 User name okay, need password."
#define NEED_ACC "332 Need account for login."
#define BAD_PASS "421 Bad password."
#define BAD_PATH "421 Bad path."
#define REQUEST_PORT "421 PASV or PORT requested."
#define ALREADY_CONNECTED "421 Already connected."
#define CONNECT_FAIL "421 Connection failed."
#define FILE_ERROR "421 File couldn't be create."
#define FILE_NOT_EXIST "421 Permission denied, closing data connection."
#define PERM_DENIED "421 Permission denied."
#define BAD_CMD "500 Bad command."
#define BAD_LOG "530 Bad login."
#define NOT_CONNECTED "530 You are not connected."

#define HELP_USER "\tUSER <SP> <username> <CRLF>   : Specify user for authentication"
#define HELP_PASS "\tPASS <SP> <password> <CRLF>   : Specify password for authentication"
#define HELP_CWD "\tCWD  <SP> <pathname> <CRLF>   : Change working directory"
#define HELP_CDUP "\tCDUP <CRLF>                   : Change working directory to parent directory"
#define HELP_QUIT "\tQUIT <CRLF>                   : Disconnection"
#define HELP_DEL "\tDELE <SP> <pathname> <CRLF>   : Delete file on the server"
#define HELP_PWD "\tPWD  <CRLF>                   : Print working directory"
#define HELP_PASV "\tPASV <CRLF>                   : Enable \"passive\" mode for data transfer"
#define HELP_PORT "\tPORT <SP> <host-port> <CRLF>  : Enable \"active\" mode for data transfer"
#define HELP_HELP "\tHELP [<SP> <string>] <CRLF>   : List available commands"
#define HELP_NOOP "\tNOOP <CRLF>                   : Do nothing"
#define HELP_DATA "\r\n\t(the following are commands using data transfer)\r\n\r\n"
#define HELP_RETR "\tRETR <SP> <pathname> <CRLF>   : Download file from server to client"
#define HELP_STOR "\tSTOR <SP> <pathname> <CRLF>   : Upload file from client to server"
#define HELP_LIST "\tLIST [<SP> <pathname>] <CRLF> : List files in the current working directory"
