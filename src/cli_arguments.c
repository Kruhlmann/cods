#include "cli_arguments.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void read_flags_into_configuration(Configuration *config, int arg_count,
                                   char *args[]) {
    size_t i;
    for (i = 1; i < arg_count && args[i][0] == '-'; i++) {
        switch (args[i][1]) {
        case CLI_FLAG_VERBOSE:
            config->verbose = true;
            break;
        case CLI_FLAG_SEND_STDOUT:
            config->to_std_out = true;
            break;
        default:
            fprintf(stderr, "Usage: %s [-%c%c] [...files]\n", args[0],
                    CLI_FLAG_VERBOSE, CLI_FLAG_SEND_STDOUT);
            exit(EXIT_FAILURE);
        }
    }
}

Configuration get_default_config() {
    Configuration default_config;
    default_config.verbose = CONFIG_DEFAULT_VERBOSE;
    default_config.to_std_out = CONFIG_DEFAULT_TO_STDOUT;

    return default_config;
}

Configuration read_command_line_arguments(int arg_count, char *args[]) {
    Configuration config = get_default_config();
    read_flags_into_configuration(&config, arg_count, args);

    return config;
}
