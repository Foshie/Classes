#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "parser.h"

#define streq(a,b)  (! strcmp((a), (b)))

/* Changes \\ to \ and \" to " */
static char *unescape(char *str);
/* Counts how many characters exist from the beginning of str until
 * the stop character.  If escapes is non-zero, backslashes cause the
 * following character to not be examined to see if it's the stop
 * character. */
static int slurp_chars(char *str, char stop, int escapes);
/**
 * The string parameter is parsed according to the rules bash uses in
 * dividing a command line into arguments, and tokens are placed in the
 * pre-allocated tokens parameter.
 *
 * -1 is returned if either parameter is NULL, or if there is an unmatched
 * single or double quote.  Otherwise, the number of tokens found is returned.
 *
 * These are the parsing rules:
 *
 * 1) Unescaped whitespace outside of a quote pair ('...' or "...")
 *    separates arguments.
 * 2) Within single quotes, backslashes have no special effects.
 * 3) Within double quotes, backslashes have a special effect only
 *    before a backslash or double quote - in the former case, the
 *    pair of backslashes will insert a single backslash into the
 *    argument, and in the latter, a double quote will be part of
 *    the argument and NOT end the argument.  Otherwise, the backslash
 *    will remain a backslash in the argument.
 * 4) Outside of any quote pair, backslashes escape all characters;
 *    escaped whitespace will NOT separate arguments.  A backslash at
 *    the end of the string causes a backslash to appear in the final
 *    argument.
 */
static int shell_words(char *str, char **tokens);

int parse_line(char *text, Command_line *cmd) {
  char *tokens[MAX_CMD_LEN] = {NULL};
  char **first, **last;
  int tok_ct;
  int i, j;

  if (text == NULL || cmd == NULL)
    return PARSE_FAIL;
  if (strlen(text) > MAX_CMD_LEN) {
    warnx("parse_line: command line too long");
    return PARSE_FAIL;
  }
  memset(cmd, 0, sizeof(*cmd));

  tok_ct = shell_words(text, tokens);

  if (tok_ct == 0) {
    warnx("parse_line: empty line");
    return PARSE_FAIL;
  }
  if (tok_ct < 0) {
    warnx("parse_line: error in tokenization");
    return PARSE_FAIL;
  }

  /* check for backgrounding */
  if (streq(TOK_BG, tokens[tok_ct - 1])) {
    tokens[tok_ct--] = NULL;
    cmd->bg = 1;
  }

  /* check for stray backgrounding tokens */
  for (i = 0; i < tok_ct; i++)
    if (streq(TOK_BG, tokens[i])) {
      warnx("parse_line: misplaced background token");
      return PARSE_FAIL;
    }

  /* check for piping, assign to argvs */
  for (i = 0, j = 0; i < tok_ct; i++) {
    if (! streq(TOK_PIPING, tokens[i])) {
      cmd->argvs[cmd->num_progs][j++] = tokens[i];
    }
    else {
      cmd->num_progs++;
      tokens[i] = NULL;
      j = 0;
    }
  }
  
  cmd->num_progs++;
  first = cmd->argvs[0];
  last = cmd->argvs[cmd->num_progs - 1];

  /* check for output redirection */
  for (i = 0; last[i]; i++)
    ;
  i -= 2;
  if (i > 0 && (streq(TOK_OUTPUT, last[i]) || streq(TOK_APPEND, last[i]))) {
    cmd->outfile = last[i+1];
    if (streq(TOK_APPEND, last[i]))
      cmd->append = 1;
    last[i] = NULL;
  }

  /* check for input redirection */
  for (i = 0; first[i]; i++)
    ;
  i -= 2;
  if (i > 0 && streq(TOK_INPUT, first[i])) {
    cmd->infile = first[i+1];
    first[i] = NULL;
  }

  /* check for stray redirection tokens */
  for (i = 0; i < cmd->num_progs; i++) {
    if (cmd->argvs[i][0] == NULL) {
      warnx("parse_line: empty command");
      return PARSE_FAIL;
    }
    for (j = 0; cmd->argvs[i][j]; j++) {
      if (streq(TOK_INPUT, cmd->argvs[i][j])
          || streq(TOK_OUTPUT, cmd->argvs[i][j])
          || streq(TOK_APPEND, cmd->argvs[i][j]))
      {
        warnx("parse_line: misplaced redirection token");
        return PARSE_FAIL;
      }
    }
  }

  return PARSE_SUCCESS;
}

static char *unescape(char *str) {
  int i, j;

  for (i = 0, j = 0; str[i]; i++, j++) {
    if (str[i] == '\\')
      if (str[i+1] == '\\' || str[i+1] == '"')
        i++;
    if (i != j)
      str[j] = str[i];
  }
  str[j] = '\0';
  return str;
}

static int slurp_chars(char *str, char stop, int escapes) {
  int i;

  for (i = 0; i < strlen(str) && str[i] != stop; i++)
    if (escapes && str[i] == '\\')
      i++;
  return str[i] == stop ? i : -1;
}

static int shell_words(char *str, char **tokens) {
  int tok_ct = 0;
  char current_arg[MAX_CMD_LEN];

  if (str == NULL || strlen(str) > MAX_CMD_LEN)
    return -1;
  
  while (isspace(*str))  /* strip leading whitespace */
    str++;
  while (*str) {
    char *start = str;
    strcpy(current_arg, "");
    while (*str && ! isspace(*str)) {
      if (*str == '"' || *str == '\'') {  /* handle quoted arguments */
        int offset;
        char ch = *str;
        if (( offset = slurp_chars(++str, ch, ch == '"') ) < 0)
          return -1;
        str[offset] = '\0';
        strcat(current_arg, ch == '"' ? unescape(str) : str);
        str += offset + 1;
      }
      else if (*str == '\\') {  /* unescape character */
        str++;
        if (*str) {
          strncat(current_arg, str, 1);
          str++;
        }
        else
          strcat(current_arg, "\\");
      }
      else {  /* add non-whitespace chars */
        strncat(current_arg, str, 1);
        str++;
      }
    }
    if (*str)
      str++;
    strcpy(start, current_arg);
    tokens[tok_ct++] = start;
    while (isspace(*str))  /* strip post-argument whitespace */
      str++;
  }
  return tok_ct;
}
