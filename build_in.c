#include <string.h>
#include "build_in.h"
#include "functions.h"

#define num_buildins 8

int isbuildin(char *s)
{
	BuildInType command = NO;

	if(!strcmp(s, "cd"))
		command = CD;
	else if (!strcmp(s, "help"))
		command = HELP;
	else if (!strcmp(s, "exit"))
		command = EXIT;
	else if (!strcmp(s, "man"))
		command = MAN;
  else if (!strcmp(s, "cat"))
  	command = CAT;
	else if (!strcmp(s, "touch"))
  	command = TOUCH;
  else if (!strcmp(s, "rm"))
  	command = RM;
  else if (!strcmp(s, "cp"))
    command = CP;

  return command;
}

int runbuildin(BuildInType command,char **args)
{
	switch(command)
	{
		case CD:
			psh_cd(args);
			break;
		case HELP:
			psh_help(args);
			break;
		case EXIT:
			psh_exit(args);
			break;
		case MAN:
      psh_man(args);
    case CAT:
      psh_cat(args);
      break;
    case TOUCH:
      psh_touch(args);
      break;
    case RM:
      psh_rm(args);
		  break;
    case CP:
      psh_cp(args);
      break;
		case NO:/* nothing */
		default:break;
	}
  return 1;
}

int psh_num_builtins()
{
	return num_buildins;
}
