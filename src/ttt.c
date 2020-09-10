#include "cli_arguments.h"
#include "filebuffer.h"
#include "xml_parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int arg_count, char *args[]) {
    Configuration *config = read_command_line_arguments(arg_count, args);
    XMLDocument document;
    load_xml_document(&document, "test.xml");
    printf("%s", read_ascii_file("test.xml"));
    printf("%s %s", document.root->tag, document.root->contents);
    printf("Attributes:\n");
    for (int i = 0; i < document.root->attributes_list.length; i++) {
        XMLAttribute attribute = document.root->attributes_list.attributes[i];
        printf("\t %s => \"%s\"\n", attribute.key, attribute.value);
    }
    return 0;
}
