#include <stdbool.h>
#include <string.h>

bool string_ends_with_string(const char *haystack, const char *needle) {
    int haystack_length = strlen(haystack);
    int needle_length = strlen(needle);
    if (needle_length > haystack_length) {
        return false;
    }

    for (int i = 0; i < needle_length; i++) {
        char needle_character = needle[needle_length - i];
        char haystack_character = haystack[haystack_length - i];

        if (needle_character != haystack_character) {
            return false;
        }
    }

    return true;
}
