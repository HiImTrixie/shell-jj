#include "errorprocess.h"
#include "globals.h"
#include <stdio.h>
#include <errno.h>

int   errno;

void error_process()
{
	switch(errno)
	{
	case E2BIG:fprintf(stderr, "PSH: Argument list too long\n");
		   break;
	case EACCES:fprintf(stderr, "PSH: %s: Permission denied\n", commands);
		    break;
	case EBUSY:fprintf(stderr, "PSH: Device or resource busy\n");
		   break;
	case EEXIST:fprintf(stderr, "PSH: File exists\n");
		    break;
	case EFBIG:fprintf(stderr, "PSH: File too large\n");
		   break;
	case EINVAL:fprintf(stderr, "PSH: Invalid argument\n");
		    break;
	case EIO:fprintf(stderr, "PSH: Input/output error\n");
		 break;
	case EISDIR:fprintf(stderr, "PSH: %s: Is a dirextory\n", commands);
		    break;
	case ENODEV:fprintf(stderr, "PSH: No such device\n");
		    break;
	case ENOENT:fprintf(stderr, "PSH: %s: command not found\n", commands);
		    break;
	}


	errno = 0;
}

