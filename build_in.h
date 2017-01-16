/*
 * include/build_in.h
 *
 * The build-in commands
 *
 */
#include "functions.h"
#ifndef _BUILDIN_H_
#define _BUILDIN_H_

int psh_num_builtins();

char *builtin_str[] =
{
	"cd",
	"help",
	"exit",
	"man",
	"cat",
	"touch",
	"rm",
	"cp"
};

int (*builtin_func[]) (char **) =
{
	&psh_cd,
	&psh_help,
	&psh_exit,
	&psh_man,
	&psh_cat,
	&psh_touch,
	&psh_rm,
	&psh_cp
};

#endif /* _BUILDIN_H_ */
