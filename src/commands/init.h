#ifndef CMD_INIT_H

  #define CMD_INIT_H

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

  #ifndef CMD_CC_H
    #include "cc.h"
  #endif

  void cmd_init() {
    int changes = 0;
    if (cmd.argc != 0)
      printf("! '%s init' does not expect any arguments\n", APP_TITLE);
    else {
      if (!fs_path_exists(".git") && system("git init > nul") == 0 && ++changes)
        printf("+ Initialized git repository\n");
      if (!fs_path_exists(".gitignore") && fs_create_file(".gitignore") && ++changes)
        printf("+ Created .gitignore\n");
      if (fs_read_file(commit_msg_path) == NULL && create_commit_msg_hook() && ++changes)
        printf("+ Created commit-msg hook\n");
      if (changes == 0)
        printf("! Nothing was done\n");
    }
  }

#endif