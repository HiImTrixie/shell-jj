#include "execute.h"
#include "globals.h"
#include "build_in.h"
#include "errorprocess.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void forktoexec()
{
	pid_t pid;
	int   i;                          /* index */
	int   status;                     /* child process's status */
	char  *arg_temp[MAXTOKENLEN + 1]; /* for arg array */
	BuildInType command;              /* holds the build in command type */

	if ( (command = isbuildin(tokenString)) )
		runbuildin(command);
	/* not build-in commands */
	else{
		/* fork a child to execute a program */	
		if ((pid = fork()) < 0)
			fprintf(stderr, "fork error...");
		else if (pid == 0){
			/* have parameter */
			if (arg[1][0] != 0){
				for (i = 0; strcmp(arg[i], "#") != 0; i++)
					arg_temp[i] = arg[i];
				arg_temp[i] = NULL;

				execvp(commands, arg_temp);
			}
			else{
				execlp(commands, commands, (char *)0);
			}
		}

		/* error process */
		error_process();

		/* waiting for child to exit */
		if ((pid == waitpid(pid, &status, 0)) < 0)
			fprintf(stderr, "waitpid error...");
		return ;
	}
}

