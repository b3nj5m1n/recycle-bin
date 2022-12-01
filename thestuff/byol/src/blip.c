#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <editline/readline.h>
#include <histedit.h>

#include "../vendor/chalk/chalk.h"
#include "../vendor/mpc/mpc.h"

int main(int argc, char *argv[]) {

  /* Create Some Parsers */
  mpc_parser_t *Integer = mpc_new("integer");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Blip = mpc_new("blip");

  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                     \
      integer   : /-?[0-9]+/ ;                             \
      operator  : '+' | '-' | '*' | '/' \
                 | \"add\" | \"sub\" | \"mul\" | \"div\" \
                 | '%' \
                 ; \
      expr     : <integer> | <float> | '(' <operator> <expr>+ ')' ;  \
      blip     : /^/ <operator> <expr>+ /$/ ;             \
    ",
            Integer, Operator, Expr, Blip);

  puts(CHALK_LIGHT_MAGENTA("BLIP Version " PACKAGE_VERSION));
  puts(CHALK_LIGHT_BLACK("Press Ctrl+c to Exit\n"));

  while (1) {
    puts(CHALK_ITALIC("blepl"));
    char *input = readline("> ");
    add_history(input);

    /* Attempt to parse the user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Blip, &r)) {
      /* On success print and delete the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print and delete the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Integer, Operator, Expr, Blip);

  return 0;
}
