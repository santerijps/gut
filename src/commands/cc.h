#ifndef CMD_CC_H

  #define CMD_CC_H

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

  int create_commit_msg_hook() {
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    sprintf(buf, COMMIT_MSG_TEMPLATE, CONVENTIONAL_COMMITS_REGEX, CONVENTIONAL_COMMITS_REGEX);
    return fs_write_file(commit_msg_path, buf);
  }

  int set_commit_msg_hook() {
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    sprintf(buf, COMMIT_MSG_TEMPLATE, cmd.argv[1], cmd.argv[1]);
    return fs_write_file(commit_msg_path, buf);
  }

  int remove_commit_msg_hook() {
    return fs_remove_file(commit_msg_path);
  }

  char* get_commit_msg_hook() {
    return fs_read_file(commit_msg_path);
  }

  void cmd_cc_get() {
    char *hook = NULL;
    if (cmd.argc != 1) printf("! '%s cc get' does not expect any arguments\n", APP_TITLE);
    else {
      hook = fs_read_file(commit_msg_path);
      if (hook == NULL) printf("! commit-msg hook is not configured\n");
      else printf("Currently configured commit-msg hook:\n%s\n", hook);
    }
  }

  void cmd_cc_set() {
    switch (cmd.argc) {
      case 1:
        if (create_commit_msg_hook())
          printf("+ Set commit-msg hook to '%s'\n", CONVENTIONAL_COMMITS_REGEX);
        break;
      case 2:
        if (set_commit_msg_hook())
          printf("+ Set commit-msg hook to '%s'\n", cmd.argv[1]);
        break;
      default:
        printf("! '%s cc set' expects at most 1 argument\n", APP_TITLE);
    }
  }

  void cmd_cc_rm() {
    if (cmd.argc != 1)
      printf("! '%s cc rm' does not expect any arguments", APP_TITLE);
    else {
      if (remove_commit_msg_hook())
        printf("- Removed commit-msg hook\n");
      else
        printf("! commit-msg hook is not configured\n");
    }
  }

  void cmd_cc() {
    if (cmd.argc == 0)
      cmd_help_cc();
    else if (cmd.argc >= 1) {
      if (strcmp(cmd.argv[0], "get") == 0)
        cmd_cc_get();
      else if (strcmp(cmd.argv[0], "set") == 0)
        cmd_cc_set();
      else if (strcmp(cmd.argv[0], "rm") == 0)
        cmd_cc_rm();
      else
        printf("! Undefined argument '%s'", cmd.argv[0]);
    }
  }

#endif