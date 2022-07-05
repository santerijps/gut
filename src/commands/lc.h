#ifndef CMD_LC_H

  #define CMD_LC_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  #ifndef CFS_H
    #include "../modules/cfs/cfs.h"
  #endif

  #ifndef GUT_H
    #include "../gut.h"
  #endif

  #ifndef CMD_HELP_H
    #include "help.h"
  #endif

  #include "../licenses.h"

  char *license_names[] = {
    "CC-BY-4.0",
    "GPLv2",
    "MIT",
    "Unlicense",
  };

  char* str_to_upper(char *s) {
    int i, len;
    char *r;

    len = strlen(s);
    r = (char*) malloc(sizeof(char) * len);
    memset(r, 0, len);
    strcpy(r, s);

    for (i = 0; i < len; i++) {
      if (r[i] >= 'a' && r[i] <= 'z') {
        r[i] = r[i] - 32;
      }
    }

    return r;
  }

  void cmd_lc_list() {
    int i, size;
    if (cmd.argc != 1)
      printf("! '%s lc list' does not expect any arguments\n", APP_TITLE);
    else {
      size = (int)(sizeof(license_names) / sizeof(char*));
      for (i = 0; i < size; i++) {
        printf("%s\n", license_names[i]);
      }
    }
  }

  void cmd_lc_set() {
    int i, size;
    if (cmd.argc != 2)
      printf("! '%s lc set' expects 1 argument (license name)\n", APP_TITLE);
    else {
      size = (int)(sizeof(license_names) / sizeof(char*));
      for (i = 0; i < size; i++) {
        if (strcmp(str_to_upper(license_names[i]), str_to_upper(cmd.argv[1])) == 0) {
          if (fs_write_file("LICENSE", LICENSES[i]))
            printf("+ Set license to %s\n", license_names[i]);
          else
            printf("! Failed to write to LICENSE file\n");
          return;
        }
      }
      printf("! Undefined license '%s'\n", cmd.argv[1]);
    }
  }

  void cmd_lc() {
    if (cmd.argc == 0)
      cmd_help_lc();
    else if (cmd.argc >= 1) {
      if (strcmp(cmd.argv[0], "list") == 0)
        cmd_lc_list();
      else if (strcmp(cmd.argv[0], "set") == 0)
        cmd_lc_set();
      else
        printf("! Undefined argument '%s'\n", cmd.argv[0]);
    }
  }

#endif