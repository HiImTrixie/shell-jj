/*! \file man.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.2
 *  \brief Wyświetl dokumentacje funkcji
 *  \details Program wyświetlający dokumentacje wskazanego pliku jako argument.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_(char *name)
{
  FILE *file;
	int c;
  char dest[64]="../man/";
  strcat(dest,name);
  strcat(dest,".txt");
  file = fopen(dest, "r");
  if(file)
  {
    while((c = getc(file)) != EOF)
      putchar(c);
    fclose(file);
  }else{
    printf("No manual entry for %s\n", name );
  }
}

int main(int argc, char **argv)
{
	if(argv[1] == NULL)
	{
		printf("You have to type what function you want to check.\n");
		printf("Example: man ls\n");
    exit(0);
	}
  read_(argv[1]);
  putchar('\n');
	return 1;
}
