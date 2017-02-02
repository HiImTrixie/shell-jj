#ifndef _BUILDIN_H_
#define _BUILDIN_H_

typedef enum{
	NO, CD, HELP, EXIT, MAN, CAT, TOUCH, RM, CP, HISTORY
}BuildInType;

int isbuildin(char *s);

void runbuildin(BuildInType command);

#endif 

