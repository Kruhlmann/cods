#include "xml_parser.h"
#include "filebuffer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

XMLNode *make_xml_node(XMLNode *parent) {
    XMLNode *node = (XMLNode *)malloc(sizeof(XMLNode));
    node->tag = NULL;
    node->contents = NULL;
    node->parent = parent;
    initialize_xml_attribute_list(&node->attributes_list);
    initialize_xml_node_list(&node->children);
    if (parent) {
        add_node_to_nodelist(&parent->children, node);
    }
    return node;
}

XMLNode *get_xml_node_child(XMLNode *parent, int child_index) {
    return parent->children.nodes[child_index];
}

void free_xml_node(XMLNode *node) {
    if (node->tag) {
        free(node->tag);
    }
    if (node->contents) {
        free(node->contents);
    }
    for (int i = 0; i < node->attributes_list.length; i++) {
        free_xml_attribute(&node->attributes_list.attributes[i]);
    }
    free(node);
}

void initialize_xml_attribute_list(XMLAttributeList *attribute_list) {
    attribute_list->heap_size = 1;
    attribute_list->length = 0;
    attribute_list->attributes =
        (XMLAttribute *)malloc(sizeof(XMLAttribute) * attribute_list->length);
}

void add_attribute_to_attribute_list(XMLAttributeList *attribute_list,
                                     XMLAttribute *attribute) {
    while (attribute_list->length >= attribute_list->heap_size) {
        int memory_to_allocate =
            sizeof(XMLAttribute) * attribute_list->heap_size;
        attribute_list->heap_size *= 2;
        attribute_list->attributes = (XMLAttribute *)realloc(
            attribute_list->attributes, memory_to_allocate);
    }

    attribute_list->attributes[attribute_list->length++] = *attribute;
}

void initialize_xml_node_list(XMLNodeList *node_list) {
    node_list->heap_size = 1;
    node_list->length = 0;
    node_list->nodes =
        (XMLNode **)malloc(sizeof(XMLNode *) * node_list->length);
}

void add_node_to_nodelist(XMLNodeList *node_list, XMLNode *node) {
    while (node_list->length >= node_list->heap_size) {
        int memory_to_allocate = sizeof(XMLNode *) * node_list->heap_size;
        node_list->heap_size *= 2;
        node_list->nodes =
            (XMLNode **)realloc(node_list->nodes, memory_to_allocate);
    }

    node_list->nodes[node_list->length++] = node;
}

void free_xml_attribute(XMLAttribute *attribute) {
    free(attribute->key);
    free(attribute->value);
}

bool load_xml_document(XMLDocument *document, char *file_path) {
    char *file_contents = read_ascii_file(file_path);
    if (!file_contents) {
        return false;
    }

    document->file_path = file_path;
    document->root = make_xml_node(NULL);

    char character_buffer[65536];
    int character_buffer_index = 0;
    int file_contents_index = 0;

    XMLNode *current_node = NULL;

    while (file_contents[file_contents_index] != '\0') {
        if (file_contents[file_contents_index] == '<') {
            character_buffer[character_buffer_index] = '\0';

            // Inner text
            if (character_buffer_index > 0) {
                if (!current_node) {
                    fprintf(stderr, "Text outside of document\n");
                    return false;
                }
                current_node->contents = strdup(character_buffer);
                character_buffer_index = 0;
            }

            // End node
            if (file_contents[file_contents_index + 1] == '/') {
                file_contents_index += 2;
                while (file_contents[file_contents_index] != '>') {
                    char next_character = file_contents[file_contents_index++];
                    character_buffer[character_buffer_index++] = next_character;
                }
                character_buffer[character_buffer_index] = '\0';

                if (!current_node) {
                    fprintf(stderr, "Root node was not opened\n");
                    return false;
                }

                if (strcmp(current_node->tag, character_buffer)) {
                    fprintf(stderr, "Tag mismatch (%s does not match %s)\n",
                            current_node->tag, character_buffer);
                    return false;
                }

                current_node = current_node->parent;
                file_contents_index++;
                continue;
            }

            if (!current_node) {
                current_node = document->root;
            } else {
                current_node = make_xml_node(current_node);
            }

            // Beginning of tag
            file_contents_index++;
            XMLAttribute current_attribute = {0, 0};
            while (file_contents[file_contents_index] != '>') {
                char next_character = file_contents[file_contents_index++];
                character_buffer[character_buffer_index++] = next_character;

                bool char_is_space = file_contents[file_contents_index] == ' ';
                bool no_current_tag = !current_node->tag;
                // tag name
                if (char_is_space && no_current_tag) {
                    character_buffer[character_buffer_index] = '\0';
                    current_node->tag = strdup(character_buffer);
                    // Reset character buffer
                    character_buffer_index = 0;
                    file_contents_index++;
                    continue;
                }

                bool last_char_was_space =
                    file_contents[file_contents_index - 1] == ' ';
                // Ignore spaces
                if (last_char_was_space) {
                    character_buffer_index--;
                    continue;
                }

                bool char_is_equals = file_contents[file_contents_index] == '=';
                // Attribute key
                if (char_is_equals) {
                    character_buffer[character_buffer_index] = '\0';
                    current_attribute.key = strdup(character_buffer);
                    character_buffer_index = 0;
                }

                bool char_is_single_quote =
                    file_contents[file_contents_index] == '\'';
                bool char_is_double_quote =
                    file_contents[file_contents_index] == '\"';
                // Attribute value
                if (char_is_single_quote || char_is_double_quote) {
                    if (!current_attribute.key) {
                        fprintf(stderr, "Attribute value has no key\n");
                        return false;
                    }
                    char quote = file_contents[file_contents_index];

                    character_buffer_index = 0;
                    file_contents_index++;

                    while (file_contents[file_contents_index] != quote) {
                        char next_character =
                            file_contents[file_contents_index++];
                        character_buffer[character_buffer_index++] =
                            next_character;
                    }
                    character_buffer[character_buffer_index] = '\0';
                    current_attribute.value = strdup(character_buffer);
                    add_attribute_to_attribute_list(
                        &current_node->attributes_list, &current_attribute);
                    current_attribute.key = NULL;
                    current_attribute.value = NULL;

                    character_buffer_index = 0;
                    file_contents_index++;
                    continue;
                }
            }
            character_buffer[character_buffer_index] = '\0';
            if (!current_node->tag) {
                current_node->tag = strdup(character_buffer);
            }
            // Reset lexer
            character_buffer_index = 0;
            file_contents_index++;
            continue;
        } else {
            char next_character = file_contents[file_contents_index++];
            character_buffer[character_buffer_index++] = next_character;
        }
    }

    return true;
}

void free_xml_document(XMLDocument *document) { free_xml_node(document->root); }
