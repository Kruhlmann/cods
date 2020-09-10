#include "cli_arguments.h"
#include "filebuffer.h"
#include "minunit.h"
#include "string.h"
#include "xml_parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

MU_TEST(test_load_document) {
    /*Configuration *config = read_command_line_arguments(arg_count, args);*/
    XMLDocument document;

    bool loaded_missing_document =
        load_xml_document(&document, "non-existant-file");
    mu_check(!loaded_missing_document);

    bool loaded_invalid_document =
        load_xml_document(&document, "res/invalid_xml.xml");
    printf("%s", document.root->contents);
    mu_check(!loaded_invalid_document);

    bool loaded_valid_document =
        load_xml_document(&document, "res/valid_xml.xml");
    mu_check(loaded_valid_document);

    XMLNode *main = get_xml_node_child(document.root, 0);
    XMLNode *secondary_node = get_xml_node_child(document.root, 1);

    printf("%d", main->children.length);
    printf("%d", secondary_node->children.length);

    free_xml_document(&document);
}
