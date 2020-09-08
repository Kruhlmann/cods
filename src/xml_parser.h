#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <stdbool.h>

struct _XMLNode {
    char *tag;
    char *contents;
    struct _XMLNode *parent;
};
typedef struct _XMLNode XMLNode;

struct _XMLDocument {
    char *file_path;
    XMLNode *root;
};
typedef struct _XMLDocument XMLDocument;

bool load_xml_document(XMLDocument *document, char *file_path);
void unload_xml_document(XMLDocument *document);
XMLNode *make_xml_node(XMLNode *parent);
void free_xml_node(XMLNode *node);

#endif
