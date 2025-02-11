#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
	memset(clist, 0, sizeof(command_list_t));
	char *command;
	char *saveptr;
	int cmd_index = 0;

	command = strtok_r(cmd_line, "|", &saveptr);
	while (command) {
		if (cmd_index >= CMD_MAX) {
			return ERR_TOO_MANY_COMMANDS;
		}

		while (*command == ' '){
			command++;
		}

		char *end = command + strlen(command) - 1;
		while (end > command && *end == ' ') {
			*end = '\0';
			end--;
		}
		char *args;
		char *exe = strtok_r(command, " ", &args);
		if (strlen(exe) > EXE_MAX) {
			return ERR_CMD_OR_ARGS_TOO_BIG;
		}

		strcpy(clist->commands[cmd_index].exe, exe);

		if (args && strlen(args) > ARG_MAX) {
			return ERR_CMD_OR_ARGS_TOO_BIG;
		}

		if (args) {
			strcpy(clist->commands[cmd_index].args, args);
		}
		else {
			clist->commands[cmd_index].args[0] = '\0';
		}
		cmd_index++;
		command = strtok_r(NULL, "|", &saveptr);
	}

	clist->num = cmd_index;
	return OK;
}
