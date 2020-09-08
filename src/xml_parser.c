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
    return node;
}

void free_xml_node(XMLNode *node) {
    if (node->tag) {
        free(node->tag);
    }
    if (node->contents) {
        free(node->contents);
    }
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
                    fprintf(stderr, "Tag mismatch (%s does not match %s)",
                            current_node->tag, character_buffer);
                    return false;
                }

                current_node - current_node->parent;
                file_contents_index++;
                continue;
            }

            if (!current_node) {
                current_node = document->root;
            } else {
                current_node = make_xml_node(current_node);
            }
            file_contents_index++;

            // Tag name
            while (file_contents[file_contents_index] != '>') {
                char next_character = file_contents[file_contents_index++];
                character_buffer[character_buffer_index++] = next_character;
            }
            character_buffer[character_buffer_index] = '\0';
            current_node->tag = strdup(character_buffer);

            // Reset character buffer
            character_buffer_index = 0;
            file_contents_index++;
            continue;
        }

        char next_character = file_contents[file_contents_index++];
        character_buffer[character_buffer_index] = next_character;
    }

    return true;
}

void unload_xml_document(XMLDocument *document) {
    free_xml_node(document->root);
}
