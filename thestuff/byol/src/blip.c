#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <editline/readline.h>
#include <histedit.h>

#include "../vendor/chalk/chalk.h"

int main (int argc, char *argv[])
{
    puts(CHALK_LIGHT_MAGENTA("BLIP Version " PACKAGE_VERSION));
    puts(CHALK_LIGHT_BLACK("Press Ctrl+c to Exit\n"));

    while (1) {
        puts(CHALK_ITALIC("blepl"));
        char* input = readline("> ");
        add_history(input);
        free(input);
    }


    return 0;
}
