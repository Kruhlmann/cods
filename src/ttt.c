#include "cli_arguments.h"
#include "filebuffer.h"
#include "xml_parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int arg_count, char *args[]) {
    Configuration *config = read_command_line_arguments(arg_count, args);
    XMLDocument document;
    load_xml_document(&document, "test.xml");

    XMLNode *child_1 = get_xml_node_child(document.root, 0);
    XMLNode *grandchild1 = get_xml_node_child(child_1, 0);

    printf("%s -> %s", grandchild1->tag, grandchild1->contents);

    XMLNode *child_2 = get_xml_node_child(document.root, 1);
    printf("%s -> %s", child_2->tag, child_2->contents);

    free_xml_document(&document);

    return 0;
}
