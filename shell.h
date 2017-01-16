/*
 * include/shell.h
 *
 * Some commands
 *
 */

#ifndef _SHELL_H_
#define _SHELL_H_

#define PSH_TOK_BUFSIZE 64
#define PSH_TOK_DELIM " \t\r\n\a"

int psh_launch(char **args);

int psh_execute(char **args);

char **psh_split_line(char *line);

char *psh_read_line(void);

void psh_loop(void);


#endif /* SHELL_H */
