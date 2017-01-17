/*
 * include/build_in.h
 *
 * The build-in commands
 *
 */

#ifndef _BUILDIN_H_
#define _BUILDIN_H_
#include "functions.h"

typedef enum{
	NO, CD, HELP, EXIT, MAN, CAT, TOUCH, RM, CP
}BuildInType;

int isbuildin(char *s);

void runbuildin(BuildInType command);

int psh_num_builtins();

#endif /* _BUILDIN_H_ */
