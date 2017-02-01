/*! \file rm.c
 *  \author Grzegorz Jaworski
 *  \date 1 Luty 2017
 *  \version   v0.2
 *  \brief Program usuwający podany plik
 *  \details Program usuwa podane jako argumenty pliki.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // library with isprint()
#include <getopt.h>

char version[64] = "v.0.2"; /*!< Aktualna wersja programu */


// Content of help
static char const * const option_help[] =
{
"Some of useful options.\n\n",
"  -v --version  Show version of program.",
"  -h --help  Output this help.",
0
};

/*! \brief Struktura zawierająca opcje programu.
 *
 *  Funcja zawierająca długie opcje pliku wywoływane przy pomocy podwójnego myślnika na przykład:--show-all .
 */
static struct option const long_options[] =
{
  {"version", 0, 0, 'v'},
  {"help", 0, 0, 'h'},
  {0, 0, 0, 0}
};

/*! \brief Funkcja wyświetla zawartość pomocy.
 *
 *  Funcja uruchamiana gdy użytkownik wpisze --help lub -h, wyświetla ona zawartość pomocy oraz przykładowe użycie.
 */
void usage()
{
  printf ("Usage: rm [OPTION]... [FILE]...\nRemove inserted arguments.\n\n");
  for (int i=0 ; option_help[i] != 0; i++)
    printf ("%s\n", option_help[i]);
}

/*! \brief Funkcja (wyświetla błąd)* oraz podpowiedz użycia pomocy.
 *
 *  Funcja wyświetla aktualny błąd jeżeli takowy wystąpił oraz podpowiedz użycia komendy wyświetlającej pomoc.
 */
static void try_help (char const *reason)
{
  if (reason)
    fprintf (stderr, "%s \n", reason);
  printf ("Try 'rm --help' for more information.\n");
  exit(EXIT_FAILURE);
}

/*! \brief Funkcja wyświetla aktualna wersje programu.
 *
 * Funkcja wyświetla wersje programu po podaniu jako argumentu -v oraz zamyka program.
 */
void pversion()
{
  printf ("RM\nVersion: %s\n", version);
  exit(-1);
}


int main(int argc, char **argv)
{
  int c, index;

  while ((c = getopt_long (argc, argv,
          "vh",
          long_options, 0)) != EOF){

    switch (c)
    {
      case 'v':

        pversion();
        exit (0);

      case 'h':
        usage();
        exit (0);

      case '?':
        if (optopt == 'c'){
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
          try_help(0);
        }
        else if (isprint (optopt)){
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
          try_help(0);
        }
        else {
          fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
          try_help(0);
        }
        return 1;

        default:
          try_help (0);
      }
  }
  if (argc == optind){
    try_help("Inserte at least one argument");
  }
  else if (optind >= argc) {
    try_help("Expected argument after options");
  }
  else{
    if( remove( argv[optind] ) != 0 )
      perror( "Error deleting file" );
  }
  return 0;
}
