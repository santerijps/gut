#ifndef CMD_HELP_H

  #define CMD_HELP_H

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

  void cmd_help_init() {
    printf(
      "Usage: %s init\n"
      "\n"
      "Initializes a new git repository and does a few extra things:\n"
      "\n"
      "  - Sets the default Conventional Commits commit-msg hook\n"
      "  - Creates a .gitignore file\n"
      "\n"
      "It does not replace any existing configurations or files, and may indeed do nothing.\n"
      "Thus, this command can be used safely.\n"
      "\n"
      , APP_TITLE
    );
  }

  void cmd_help_cc() {
    printf(
      "Usage: %s cc [sub]\n"
      "\n"
      "Where sub is one of:\n"
      "\n"
      "  get         \tPrints the commit-msg hook currently in use.\n"
      "  set <value?>\tSets the commit-msg hook to some RegEx value.\n"
      "              \tWithout any provided value, the default Conventional Commits hook is used.\n"
      "  rm          \tRemoves the currently configured commit-msg hook.\n"
      "\n"
      , APP_TITLE
    );
  }

  void cmd_help_lc() {
    printf(
      "Usage: %s lc [sub]\n"
      "\n"
      "Where sub is one of:\n"
      "\n"
      "  list         \tLists all available licenses in gut.\n"
      "  set <lic>    \tSet the repository license. Must match the names in 'gut lc list'.\n"
      "\n"
      , APP_TITLE
    );
  }

  void cmd_help_topic() {
    if (strcmp(cmd.argv[0], "init") == 0) cmd_help_init();
    else if (strcmp(cmd.argv[0], "cc") == 0) cmd_help_cc();
    else if (strcmp(cmd.argv[0], "lc") == 0) cmd_help_lc();
    else printf("! Undefined topic '%s'", cmd.argv[0]);
  }

  void cmd_help() {
    if (cmd.argc == 0) print_basic_usage();
    else if (cmd.argc == 1) cmd_help_topic();
    else printf("! '%s help' expects at most 1 argument\n", APP_TITLE);
  }

#endif