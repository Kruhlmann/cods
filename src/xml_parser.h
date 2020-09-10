#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <stdbool.h>

struct _XMLAttribute {
    char *key;
    char *value;
};
typedef struct _XMLAttribute XMLAttribute;

struct _XMLAttributeList {
    int heap_size;
    int length;
    XMLAttribute *attributes;
};
typedef struct _XMLAttributeList XMLAttributeList;

struct _XMLNode {
    char *tag;
    char *contents;
    XMLAttributeList attributes_list;
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
void initialize_xml_attribute_list(XMLAttributeList *attribute_list);
void add_attribute_to_attribute_list(XMLAttributeList *attribute_list,
                                     XMLAttribute *attribute);
void free_xml_node(XMLNode *node);
void free_xml_attribute(XMLAttribute *attribute);

#endif
