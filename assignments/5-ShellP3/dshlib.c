#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
void build_cmd(char *cmd_line, cmd_buff_t *cmd) {
    memset(cmd, 0, sizeof(cmd_buff_t));
    cmd->_cmd_buffer = malloc(ARG_MAX);

    while (*cmd_line == ' ') {
    	cmd_line++;
    }

    char *end = cmd_line + strlen(cmd_line) - 1;
    while (end > cmd_line && *end == ' ') {
    	*end = '\0';
    	end--;
    }

    strcpy(cmd->_cmd_buffer, cmd_line);
	char *arg = cmd->_cmd_buffer;
	while (*arg) {
		while (isspace(*arg)) {
			arg++;
		}
		if (*arg == '\0') {
			break;
		}
		char *start;
		if (*arg == '"') {
			start = ++arg;
			while (*arg && *arg != '"') {
				arg++;
			}
			if (*arg == '"') {
				*arg++ = '\0';
			}
		}
		else {
			start = arg;
			while (*arg && *arg != ' ') {
				arg++;
			}
			if (*arg == ' ') {
				*arg++ = '\0';
			}
		}
		cmd->argv[cmd->argc++] = start;
	}
}

int build_list(char *cmd_line, command_list_t *clist) {
	memset(clist, 0, sizeof(command_list_t));

	char* command;
	int cmd_index = 0;
	command = strtok(cmd_line, PIPE_STRING);
	
	while(command != NULL) {
		if (clist->num == CMD_MAX) {
			return ERR_TOO_MANY_COMMANDS;
		}
		cmd_buff_t cmd_buff;
		build_cmd(command, &cmd_buff);
		clist->commands[clist->num++] = cmd_buff;
		command = strtok(NULL, PIPE_STRING);
	}
	return OK;
}

int exec_local_cmd_loop()
{
	char *cmd_buff;
	int rc = 0;
	int status;
	command_list_t clist;
	cmd_buff = malloc(ARG_MAX);

	while(1) {
		printf("%s", SH_PROMPT);
		if (fgets(cmd_buff, ARG_MAX, stdin) == NULL) {
			printf("\n");
		}

		cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

		if (strcmp(cmd_buff, EXIT_CMD) == 0) {
			rc = 0;
			free(cmd_buff);
			printf("cmd loop returned %d\n", rc);
			exit(rc);
		}

		if (strlen(cmd_buff) == 0) {
			printf(CMD_WARN_NO_CMD);
		}

		rc = build_list(cmd_buff, &clist);

		if (rc == ERR_TOO_MANY_COMMANDS) {
			printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
		}

		else {
			int pipes = clist.num - 1;
			int fds[2 * pipes];
			pid_t pid;

			for (int i = 0; i < pipes; i++){
				pipe(fds + i * 2);
			}

			for (int i = 0; i < clist.num; i++) {
				pid = fork();
				if (pid == 0) {
					if (i > 0) {
						dup2(fds[(i - 1) * 2], STDIN_FILENO);
					}
				
					if (i < clist.num - 1) {
						dup2(fds[i * 2 + 1], STDOUT_FILENO);
					}

					for (int j = 0; j < 2 * pipes; j++){ 
						close(fds[j]);
					}

					execvp(clist.commands[i].argv[0], clist.commands[i].argv);
				}
			}

			for (int i = 0; i < 2 * pipes; i++) {
				close(fds[i]);
			}

			for (int i = 0; i < clist.num; i++) {
				wait(&status);
			}

			for (int i = 0; i < clist.num; i++) {
				free(clist.commands[i]._cmd_buffer);
			}
		}
	}
}
