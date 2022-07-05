#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gut.h"
#include "commands/help.h"
#include "commands/init.h"
#include "commands/cc.h"
#include "commands/lc.h"

int main(int argc, char **argv) {

  init_app(argc, argv);

  if (f_help->is_set) {
    print_basic_usage();
    return EXIT_SUCCESS;
  }

  if (f_version->is_set) {
    printf("%s\n", APP_VERSION);
    return EXIT_SUCCESS;
  }

  cmd = cmd_parse_clargs(&args);
  check_cmd();

  return EXIT_SUCCESS;
}

void init_app(int argc, char **argv) {

  // Initialize flag parser
  fp = clargs_parser_new(argc, argv);
  f_help = clargs_flag_new_bool(&fp, "help", 'h', "Show app usage.", false);
  f_version = clargs_flag_new_bool(&fp, "version", 'v', "Show app version.", false);
  f_save = clargs_flag_new_str(&fp, "save", 's', "Save to a name.", "");
  args = clargs_parse_args(&fp);

  // Initialize paths
  app_data_dir = fs_path_join(2, fs_home_dir(), ".gut");
  app_data_current_commit_msg_path = fs_path_join(2, app_data_dir, "current.txt");
  commit_msg_path = fs_path_join(3, ".git", "hooks", "commit-msg");

  // Create .gut folder if it doesn't exist
  if (!fs_path_exists(app_data_dir)) {
    if (fs_create_dir(app_data_dir)) {
      printf("+ First time run: Created %s\n", app_data_dir);
    }
  }

  // Create current.txt if it doesn't exist
  if (!fs_path_exists(app_data_current_commit_msg_path)) {
    if (fs_create_file(app_data_current_commit_msg_path)) {
      printf("+ First time run: Created %s\n", app_data_current_commit_msg_path);
    }
  }

}

void check_cmd() {
  if (cmd.name == NULL)
    printf("! Invalid input, run '%s help' to read about usage\n", APP_TITLE);
  else if (strcmp(cmd.name, "help") == 0)
    cmd_help();
  else if (strcmp(cmd.name, "init") == 0)
    cmd_init();
  else if (strcmp(cmd.name, "cc") == 0)
    cmd_cc();
  else if (strcmp(cmd.name, "lc") == 0)
    cmd_lc();
  else
    printf("! Invalid input, run '%s help' to read about usage\n", APP_TITLE);
}

void print_basic_usage() {
  printf(
    "%s %s\n"
    "------------------------------------------\n"
    "Usage: %s [command] [options]\n"
    "   or: gut --help\n"
    "   or: gut --version\n"
    "\n"
    "Description: %s\n"
    "\n"
    "Commands:\n"
    "  init         \t\tInitialize a new git repo with some extras.\n"
    "  cc    <sub>  \t\tCommit convention utility.\n"
    "  lc    <sub>  \t\tLicense utility.\n"
    "  help  <topic>\t\tShow helpful information about commands and the app.\n"
    "\n"
    "Options:\n"
    "  -%c, --%s\t\t%s\n"
    "  -%c, --%s\t\t%s\n"
    "\n",
    APP_TITLE, APP_VERSION,
    APP_TITLE, APP_DESCRIPTION,
    f_help->short_name, f_help->long_name, f_help->description,
    f_version->short_name, f_version->long_name, f_version->description
  );
}