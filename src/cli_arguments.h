#ifndef CLI_ARGUMENTS_H
#define CLI_ARGUMENTS_H

#include <stdbool.h>
#include <stdio.h>

struct _Configuration {
    bool verbose;
    bool to_std_out;
    FILE *files[];
};
typedef struct _Configuration Configuration;

static const bool CONFIG_DEFAULT_VERBOSE = false;
static const bool CONFIG_DEFAULT_TO_STDOUT = false;

#define CLI_FLAG_VERBOSE 'v'
#define CLI_FLAG_SEND_STDOUT 'o'

void read_flags_into_configuration(Configuration *config, int arg_count,
                                   char *args[]);
Configuration get_default_config();
Configuration read_command_line_arguments(int arg_count, char *args[]);

#endif
