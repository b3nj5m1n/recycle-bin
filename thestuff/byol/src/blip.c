#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <editline/readline.h>
#include <histedit.h>

#include "../vendor/chalk/chalk.h"
#include "../vendor/mpc/mpc.h"

long eval_op(long x, char *op, long y) {
  if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) {
    return x + y;
  }
  if (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0) {
    return x - y;
  }
  if (strcmp(op, "*") == 0 || strcmp(op, "mul") == 0) {
    return x * y;
  }
  if (strcmp(op, "/") == 0 || strcmp(op, "div") == 0) {
    return x / y;
  }
  if (strcmp(op, "%") == 0 || strcmp(op, "mod") == 0) {
    return x % y;
  }
  if (strcmp(op, "^") == 0 || strcmp(op, "pow") == 0) {
    return pow(x, y);
  }
  if (strcmp(op, "min") == 0) {
    if (x < y) {
      return x;
    } else {
      return y;
    }
  }
  if (strcmp(op, "max") == 0) {
    if (x > y) {
      return x;
    } else {
      return y;
    }
  }
  return 0;
}

long eval(mpc_ast_t *t) {
  // If it's a number, return the number
  if (strstr(t->tag, "integer")) {
    return atoi(t->contents);
  }

  // Operator is second child since first child is '('
  char *op = t->children[1]->contents;

  // Eval expression after operator
  long x = eval(t->children[2]);

  // Eval remaining expressions & reduce
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

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
                 | '%' | '^' \
                 | \"mod\" | \"pow\" \
                 | \"min\" | \"max\" \
                 ; \
      expr     : <integer> | '(' <operator> <expr>+ ')' ;  \
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
      long result = eval(r.output);
      printf("%li\n", result);
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
