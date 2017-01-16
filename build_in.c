#include "build_in.h"
#include "functions.h"

int psh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}
