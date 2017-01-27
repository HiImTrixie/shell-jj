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
#include <stdlib.h>
#include <ctype.h> // library with isprint()
#include <getopt.h>

char version[64] = "v.0.1 Alpha"; /*!< Aktualna wersja programu */

// Content of help
static char const * const option_help[] =
{
"With no FILE read standard input.\n\n"
"-A  --show-all  Show all lines contained in files.",
"-v --version  Show version of program."
"--help  Output this help.",
0
};

/*! \brief Struktura zawierająca opcje programu.
 *
 *  Funcja zawierająca długie opcje pliku wywoływane przy pomocy podwójnego myślnika na przykład:--show-all .
 */
static struct option const long_options[] =
{
  {"show-all", 0, 0, 'a'},
  {"recursive", 0, 0, 'r'},
  {"report-identical-files", 0, 0, 's'},
  {"help", 0, 0, 'h'},
  {0, 0, 0, 0}
};

/*! \brief Funkcja wyświetla zawartość pomocy.
 *
 *  Funcja uruchamiana gdy użytkownik wpisze --help lub -h, wyświetla ona zawartość pomocy oraz przykładowe użycie.
 */
void usage()
{
  printf ("Usage: cat [OPTION]... [FILE]...\nConcatenate FILE(s) to standard outup.\n\n");
  for (int i=0 ; option_help[i] != 0; i++)
    printf ("  %s\n", option_help[i]);
  printf ("\nIf FILE1 or FILE2 is `-', read standard input.\n");
}

/*! \brief Funkcja (wyświetla błąd)* oraz podpowiedz użycia pomocy.
 *
 *  Funcja wyświetla aktualny błąd jeżeli takowy wystąpił oraz podpowiedz użycia komendy wyświetlającej pomoc.
 */
static void try_help (char const *reason)
{
  if (reason)
    fprintf (stderr, "%s \n", reason);
  printf ("Try 'cat --help' for more information.\n");
  exit(EXIT_FAILURE);
}

/*! \brief Funkcja wyświetla aktualna wersje programu.
 *
 * Funkcja wyświetla wersje programu po podaniu jako argumentu -v oraz zamyka program.
 */
void pversion()
{
  printf ("Cat\nVersion: %s\n", version);
  exit(-1);
}
void cat(char *name)
{
  FILE *file;
  int c;
  file = fopen(name, "r");
  if(file)
  {
    while((c = getc(file)) != EOF)
      putchar(c);
    fclose(file);
  }
}


int main(int argc, char **argv)
{
  int c, index;

  while ((c = getopt_long (argc, argv,
          "Avh",
          long_options, 0)) != EOF){

    switch (c)
    {
      case 'A':
        break;

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
  if (optind == argc){
    printf("Read standard input\n");
  }
  else if (optind >= argc) {
    try_help("Expected argument after options");
  }
  else{
    for (index=0; optind < argc; index++){
      cat(argv[optind]);
      optind++;
    }
  }
  return 0;
}
