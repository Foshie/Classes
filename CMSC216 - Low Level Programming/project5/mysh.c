#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "wait.h"
#include <unistd.h>
#include "parser.h"
#include "execute.h"

static void change_directory(const char *filename);

int main() {
  Command_line cmd;
  char buffer[MAX_CMD_LEN];

  while (1) {
    printf("mysh-0.9$ ");
    fflush(stdout);

    /* read a line, quit if EOF */
    if (fgets(buffer, MAX_CMD_LEN, stdin) == NULL)
      break;

    /* back to prompt if fail to parse */
    if (parse_line(buffer, &cmd) == PARSE_FAIL)
      continue;

    /* quit if user asked to exit */
    if (strcmp(cmd.argvs[0][0], "exit") == 0)
      break;

    /* this has to be a shell built-in, so we handle it here */
    if (strcmp(cmd.argvs[0][0], "cd") == 0) {
      change_directory(cmd.argvs[0][1]);
      continue;
    }

    /* do the magic */
    execute_command_line(&cmd);
  }
  return 0;
}

static void change_directory(const char *filename) {
  if (filename == NULL || strcmp(filename, "~") == 0)
    filename = getenv("HOME");
  if (chdir(filename) < 0)
    warn("can't change directory");
}
