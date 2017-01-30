/*! \file rm.c
 *  \author Grzegorz Jaworski
 *  \date 29 Styczeń 2017
 *  \version   v0.1
 *  \brief Program usuwający podany plik
 *  \details Program usuwa podane jako argumenty pliki.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
 #include <stdio.h>

int main(int argc, char **argv)
{
  if( remove( argv[1] ) != 0 )
    perror( "Error deleting file" );
  return 0;
}
