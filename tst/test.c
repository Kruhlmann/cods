
#include "cli_arguments.h"
#include "minunit.h"
#include "test_xml_parser/test_document_parser.h"

int arg_count;
char **args;
int tests_run = 0;

char *run_all_tests() {
    mu_run_test(test_load_invalid_document);
    mu_run_test(test_load_missing_document);
    mu_run_test(test_load_valid_document);
    return 0;
}

int main(int local_arg_count, char **local_args) {
    arg_count = local_arg_count;
    args = local_args;

    printf("Running tests\n");
    char *result = run_all_tests();

    if (result != 0) {
        printf("\e[31mFailed:\e[0m %s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Number of tests run: %d\n", tests_run);

    return 0;
}
