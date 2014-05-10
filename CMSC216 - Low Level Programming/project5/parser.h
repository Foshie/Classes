#if !defined(PARSER_H)
#define PARSER_H

#define MAX_CMD_LEN 256
#define MAX_ARGS (MAX_CMD_LEN + 1) / 2
#define MAX_PROGS (MAX_ARGS + 1) / 2

#define PARSE_SUCCESS 0
#define PARSE_FAIL -1

#define TOK_PIPING "|"
#define TOK_INPUT  "<"
#define TOK_OUTPUT ">"
#define TOK_APPEND ">>"
#define TOK_BG     "&"

/* This is the structure that holds the information about a parsed
 * command line.  The argvs array is an array of string vectors; in
 * other words, for some int i, argvs[i] is an array of strings.
 * You should be able to use argvs[i] in calls to one of the execv*()
 * functions.
 */
typedef struct {
  char *argvs[MAX_PROGS + 1][MAX_ARGS + 1];
  int num_progs;  /* Number of argument vectors; if > 1, piping is requested */
  char *infile;   /* Name of stdin redirect file; NULL if no redirection */
  char *outfile;  /* Name of stdout redirect file; NULL if no redirection */
  int append;     /* Is output redirection appending? */
  int bg;         /* Put command into background? */
} Command_line;


int parse_line(char *text, Command_line *cmd);

#endif
