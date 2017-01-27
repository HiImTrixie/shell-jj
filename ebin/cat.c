/*! \file cat.c
 *  \author Grzegorz Jaworski
 *  \date 27 Styczeń 2017
 *  \version   v0.1
 *  \brief Wyświetlanie zawartości pliku
 *  \details Program wyświetlajacy zawartość wskazanych plików
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */

#include <stdio.h>

int main(int argc, char **argv)
{
  FILE *file;
  int c;
  if(argv[1] == NULL)
  {
    fprintf(stderr, "No file were given\n");
    return 1;
  }
  else
  {
    file = fopen(argv[1], "r");
    if(file)
    {
      while((c = getc(file)) != EOF)
      putchar(c);
			fclose(file);
		}
	}
	return 0;
}
