/*! \file man.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.1
 *  \brief Wyświetl dokumentacje funkcji
 *  \details Program wyświetlający dokumentacje wskazanego pliku jako argument.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp;
	int c;
	if(argv[1] == NULL)
	{
		printf("You have to type what function you want to check.\n");
		printf("Example: man ls\n");
	}
	else if(strcmp(argv[1], "cd") == 0)
	{
		fp = fopen("../man/cd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(argv[1], "exit") == 0)
	{
		fp = fopen("../man/exit.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(argv[1], "pwd") == 0)
	{
		fp = fopen("../man/pwd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(argv[1], "ls") == 0)
	{
		fp = fopen("../man/ls.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(argv[1], "man") == 0)
	{
		fp = fopen("../man/man.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(argv[1], "cat") == 0)
	{
		fp = fopen("../man/cat.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
  putchar('\n');
	return 1;
}
