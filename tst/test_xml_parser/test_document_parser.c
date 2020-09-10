#include "../minunit.h"
#include "xml_parser.h"
#include <stdbool.h>

char *test_load_missing_document() {
    XMLDocument document;
    bool loaded = load_xml_document(&document, "non-existing-file");
    mu_assert("was able to load a non-existing xml file", !loaded);
    return 0;
}

char *test_load_valid_document() {
    XMLDocument document;
    bool loaded = load_xml_document(&document, "res/tests/valid_xml.xml");
    mu_assert("was unable to load valid xml file", loaded);
    return 0;
}

char *test_load_invalid_document() {
    XMLDocument document;
    bool loaded = load_xml_document(&document, "res/tests/invalid_xml.xml");
    mu_assert("was able to load invalid xml file", !loaded);
    return 0;
}
