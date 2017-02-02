#include "globals.h"
#include "readline.h"
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char pwd[MAXTOKENLEN + 1];
/* for read buf */
static char *line_read = (char *)0;
/* for commands auto-completion */
char **command_completion(const char *, int, int);
char *command_generator(const char *, int);
char *commandarray[] = {"cd", "pwd", "history", "exit"};

char *rl_gets()
{
	rl_attempted_completion_function = command_completion;
	if (line_read){
		free(line_read);
		line_read = (char *)0;
	}

	char prompt[50];
	sprintf(prompt, "[PonyShell %s]# ", strrchr(pwd, '/') + 1);
	line_read = readline(prompt);

	if (line_read && *line_read)
		add_history(line_read); /* add command to history */
	return line_read;
}

char **command_completion(const char *text, int start, int end)
{
	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, command_generator);
}

char *command_generator(const char *text, int state)
{
	char *name;
	static int list_index, len;

	if (!state){
		list_index = 0;
		len = strlen(text);
	}

	while ( (name = commandarray[list_index++]) ){
		if (strncmp(name, text, len) == 0){
			return strdup(name);
		}
	}	

	return NULL;
}

void initialize_readline()
{
	rl_readline_name = "PSH";
	rl_attempted_completion_function = command_completion;
}

