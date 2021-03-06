/*! \file cat.c
 *  \author Grzegorz Jaworski
 *  \date 27 Styczeń 2017
 *  \version   v0.4
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

char version[64] = "v.0.4"; /*!< Aktualna wersja programu */

unsigned show_tabs = 0; /*!< Wyświetl znaki tabulacji */

unsigned show_ends = 0; /*!< Wyświetl znak końca linii */

unsigned number_ = 0; /*!< Wyświetl numer linii */

// Content of help
static char const * const option_help[] =
{
"With no FILE read standard input.\n\n",
"-A  --show-all  The same effect as -TE",
"-T  --show-tabs  Display ^I instead of TAB character.",
"-E  --show-ends  Display $ na końcu każdej linii.",
"-n  --number  Show number of the line.",
"-v --version  Show version of program.",
"-h --help  Output this help.",
0
};

/*! \brief Struktura zawierająca opcje programu.
 *
 *  Funcja zawierająca długie opcje pliku wywoływane przy pomocy podwójnego myślnika na przykład:--show-all .
 */
static struct option const long_options[] =
{
  {"show-all", 0, 0, 'A'},
  {"show-tabs", 0, 0, 'T'},
  {"show-ends", 0, 0, 'E'},
  {"number", 0, 0, 'n'},
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

/*! \brief Funkcja wyświetlająca zawartość pliku.
 *
 * Funkcja wyświetla zawartość podanego pliku jako argument *name.
 *
 * \param[in] *name Nazwa pliku z, którego ma zostać przeczytana oraz wyświetlona zawartość
 */
void cat(char *name)
{
  FILE *file;
  int c, index = 1;
  if (number_) printf("     %d  ",index++);
  file = fopen(name, "r");
  if(file)
  {
    while((c = getc(file)) != EOF){
      if(show_tabs && c=='\t')
        printf("^I");
      else if(show_ends && number_ && c=='\n')
        printf("$\n     %d  ",index++);
      else if(show_ends && c=='\n')
        printf("$\n");
      else if(number_ && c=='\n')
        printf("\n     %d  ",index++);
      else{
        putchar(c);
      }
    }
    fclose(file);
  } else
    perror( "cat: ");
}

int main(int argc, char **argv)
{
  int c, index;

  while ((c = getopt_long (argc, argv,
          "ATEnvh",
          long_options, 0)) != EOF){

    switch (c)
    {
      case 'A':
        show_tabs = 1;
        show_ends = 1;
        break;

      case 'T':
        show_tabs = 1;
        break;

      case 'E':
        show_ends = 1;
        break;

      case 'n':
        number_ = 1;
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
