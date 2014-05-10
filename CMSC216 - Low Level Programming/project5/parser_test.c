#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
#include "parser.h"

void display(Command_line *cmd) {
  int i;
  if (cmd == NULL)
    return;
  if (cmd->infile)
    printf("  Input from %s\n", cmd->infile);
  for (i = 0; i < cmd->num_progs; i++) {
    int j;
    printf("  argvs[%d]:\n", i);
    for (j = 0; cmd->argvs[i][j]; j++)
      printf("    [%d] %s\n", j, cmd->argvs[i][j]);
  }
  if (cmd->outfile)
    printf("  Output %sto %s\n", cmd->append ? "appended " : "", cmd->outfile);
  if (cmd->bg)
    printf("  Place in background\n");
  fflush(stdout);
}

int main() {
  char buffer[MAX_CMD_LEN + 1];
  Command_line cmd;

  while (fgets(buffer, MAX_CMD_LEN, stdin)) {
    /* only echo the command line if stdin isn't a terminal */
    if (! isatty(STDIN_FILENO))
      printf("Parsing %s", buffer);
    if (parse_line(buffer, &cmd) == PARSE_SUCCESS)
      display(&cmd);
    else
      printf("Failed to parse correctly.\n");
  }
  return 0;
}
