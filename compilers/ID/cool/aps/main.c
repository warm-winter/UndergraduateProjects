#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aps-tree.h"
#include "language.h"

extern void apsgen(Program);

static void usage(char *name) {
  fprintf(stderr,"%s: usage: %s <file.aps>\n",name,name);
  exit(1);
}

Program the_tree = NULL;
int aps_parse_error = 0;

int info_size = 0;

int language = CPP; /* default language is C++ */

main(int argc,char **argv) {
  extern FILE *aps_yyin;
  extern char *aps_yyfilename;

  if (strstr(argv[0], "java")) {
      language = JAVA;
  }

  if (argc != 2) usage(argv[0]);

  if ((aps_yyin = fopen(aps_yyfilename=argv[1],"r")) == NULL) {
    fprintf(stderr,"%s: cannot open file: %s\n",argv[0],argv[1]);
    exit(1);
  }
  init_lexer(aps_yyin);
  if (aps_yyparse() == 1 || aps_parse_error) {
    fprintf(stderr,"%s: quit\n",argv[0]);
    exit(1);
  }

  /* now the_tree has the tree */
  apsgen(the_tree);

  /* for debugging */
/*
  dump_lisp_Program(the_tree);
  printf("\n");
*/

  exit(0);
}

int yywrap()
{
  return 1;
}
