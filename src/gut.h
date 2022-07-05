#ifndef GUT_H

  #define GUT_H

  #ifndef CLARGS_H
    #include "modules/clargs/clargs.h"
  #endif

  #ifndef CMD_H
    #include "cmd.h"
  #endif

  #ifndef CFS_H
    #include "modules/cfs/cfs.h"
  #endif

  const char *APP_TITLE   = "gut";
  const char *APP_VERSION = "0.1.0";
  const char *APP_DESCRIPTION = "Git utilities to help with some redundant tasks.";
  const char *CONVENTIONAL_COMMITS_REGEX = "^(?:feat|fix|test|docs|refactor)(?:\\(\\w+\\))?: (?:add|update|remove) .+$";

  const char COMMIT_MSG_TEMPLATE[] =
    "#!/bin/sh\n"
    "test \"$(grep -P '%s' \"$1\")\" || {\n"
    "  echo >&2 'Commit rejected due to invalid commit message format.'\n"
    "  echo >&2 'Correct format is: %s'\n"
    "  exit 1\n"
    "}";

  FLAG_PARSER fp;
  FLAG *f_help, *f_version, *f_save;
  CLARGS args;
  CMD cmd;

  char *app_data_dir;
  char *app_data_current_commit_msg_path;
  char *commit_msg_path;

  void init_app(int argc, char **argv);
  void check_cmd();
  void print_basic_usage();

#endif