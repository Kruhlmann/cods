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

struct _XMLNodeList {
    int heap_size;
    int length;
    struct _XMLNode **nodes;
};
typedef struct _XMLNodeList XMLNodeList;

struct _XMLNode {
    char *tag;
    char *contents;
    XMLAttributeList attributes_list;
    XMLNodeList children;
    struct _XMLNode *parent;
};
typedef struct _XMLNode XMLNode;

struct _XMLDocument {
    char *file_path;
    XMLNode *root;
};
typedef struct _XMLDocument XMLDocument;

XMLNode *make_xml_node(XMLNode *parent);
XMLNode *get_xml_node_child(XMLNode *parent, int child_index);

bool load_xml_document(XMLDocument *document, char *file_path);

void initialize_xml_node_list(XMLNodeList *nodes);
void add_node_to_nodelist(XMLNodeList *nodes, XMLNode *node);

void initialize_xml_attribute_list(XMLAttributeList *attribute_list);

void add_attribute_to_attribute_list(XMLAttributeList *attribute_list,
                                     XMLAttribute *attribute);

void free_xml_document(XMLDocument *document);
void free_xml_node(XMLNode *node);
void free_xml_attribute(XMLAttribute *attribute);

#endif
