#include "filebuffer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%s", read_ascii_file("test.xml"));
    return 0;
}
