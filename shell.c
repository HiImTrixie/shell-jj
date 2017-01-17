#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "build_in.h"
#include "shell.h"


int psh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		if(execvp(args[0], args) == -1)
		{
			perror("PonyShell");
		}
		exit(EXIT_FAILURE);
		}
		else if(pid < 0)
		{
			perror("PonyShell");
		}
		else
		{
			do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			}
			while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}

	return 1;

}

int psh_execute(char **args)
{
	int i;

	if(args[0] == NULL)
	{
		return 1;
	}
	if( (i = isbuildin(args[0])) != NO)
	{
		return runbuildin(i,args);
	}
	return psh_launch(args);
}

#define PSH_TOK_BUFSIZE 64
#define PSH_TOK_DELIM " \t\r\n\a"

char **psh_split_line(char *line)
{
	int bufsize = PSH_TOK_BUFSIZE, position=0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;
	if(!tokens)
	{
		fprintf(stderr, "PonyShell: Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, PSH_TOK_DELIM);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;
		if(position >= bufsize)
		{
			bufsize += PSH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "PonyShell: Allocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
	token = strtok(NULL, PSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char *psh_read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}

void psh_loop(void)
{
	char *line;
	char **args;
	int status;
	char cwd[1024];
	do
	{
		printf("%s$ ", getcwd(cwd, sizeof(cwd)));
		line = psh_read_line();
		args = psh_split_line(line);
		status = psh_execute(args);

		free(line);
		free(args);
	}
	while (status);
}
