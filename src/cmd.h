#ifndef CMD_H

  #define CMD_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  #ifndef CLARGS_H
    #include "clargs.h"
  #endif

  typedef struct CMD {
    char *name;
    char **argv;
    int argc;
  } CMD;

  CMD cmd_parse_clargs(CLARGS *clargs) {

    CMD cmd;
    int i;

    cmd.name = NULL;
    cmd.argv = NULL;
    cmd.argc = 0;

    if (clargs->size == 0) {
      return cmd;
    }

    cmd.name = clargs->values[0];
    cmd.argv = (char**) malloc(sizeof(char*) * (clargs->size - 1));
    cmd.argc = clargs->size - 1;

    for (i = 1;  i < clargs->size; i++) {
      cmd.argv[i - 1] = clargs->values[i];
    }

    return cmd;

  }

  void cmd_print(CMD *c) {
    printf("CMD { name = %s, argc = %d, argv = [", c->name, c->argc);
    for (int i = 0; i < c->argc; i++) {
      if (i == c->argc - 1) printf("%s", c->argv[i]);
      else printf("%s, ", c->argv[i]);
    }
    printf("] }\n");
  }

#endif