/*! \file cp.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.1
 *  \brief Kopiowanie pliku do innej lokacji
 *  \details Program kopiujący wskazany plik do innej lokacji.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>

void copy(char *name1, char *name2){
  FILE *file1= NULL, *file2= NULL;
  file1 = fopen(name1, "r");
  if(file1!=NULL)
  {
    file2 = fopen(name2, "w");
    char symbol;
    for(int i=0; ( symbol = fgetc(file1)) != -1; i++)
      fputc(symbol, file2);
    fclose(file1);
    fclose(file2);
  }
}

int main(int argc, char **argv)
{
  copy(argv[1],argv[2]);
  return 0;
}
