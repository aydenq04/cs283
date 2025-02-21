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

// TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff
int build_cmd(char *cmd_line, cmd_buff_t *cmd) {
	memset(cmd, 0, sizeof(cmd_buff_t));
	cmd->_cmd_buffer = malloc(ARG_MAX);

	while(*cmd_line == ' ') {
		cmd_line++;
	}

	char *end = cmd_line + strlen(cmd_line) - 1;
	while(end > cmd_line && *end == ' ') {
		*end = '\0';
		end--;
	}
		
	strcpy(cmd->_cmd_buffer, cmd_line);

	char *arg = cmd_line;
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

	return OK;
}


int exec_local_cmd_loop()
{
    char *cmd_buff;
    int rc = 0;
    cmd_buff_t cmd;
	cmd_buff = malloc(ARG_MAX);
	int status;
	
	// TODO IMPLEMENT MAIN LOOP
	while(1) {
		printf("%s", SH_PROMPT);
		if (fgets(cmd_buff, ARG_MAX, stdin) == NULL) {
			printf("\n");
		}

		cmd_buff[strcspn(cmd_buff,"\n")] = '\0';

		if (strcmp(cmd_buff, EXIT_CMD) == 0) {
			rc = 0;
			free(cmd_buff);
			printf("cmd loop returned %d\n", WEXITSTATUS(status));
			exit(rc);
		}

		if (strlen(cmd_buff) == 0) {
			printf(CMD_WARN_NO_CMD);
		}

		else {
			//TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
			// the cd command should chdir to the provided directory; if no directory is provided, do nothing
			int rc = build_cmd(cmd_buff, &cmd);
			if (cmd.argc == 2 && strcmp(cmd.argv[0], "cd") == 0) {
				chdir(cmd.argv[1]);
			}
			else if (strcmp(cmd.argv[0], "cd") != 0){
				// TODO IMPLEMENT if not built-in command, fork/exec as an external command
				// for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"
				pid_t pid = fork();
				if (pid == 0) {
					execvp(cmd.argv[0], cmd.argv);
				}
				else if (pid > 0) {
					pid = wait(&status);
				}
			}
			free(cmd._cmd_buffer);
		}
	}
    return OK;
}
