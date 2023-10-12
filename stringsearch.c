#include <stdio.h>
#include <stdlib.h>

char path[] = "/home/kali/Downloads/Mantooth_raw.dd.raw";

int stringSearch(int offset, const char* searchString) {
    char command[256];

    // Step 1: Run blkls to extract block data
    snprintf(command, sizeof(command), "blkls -o %d %s > blkfile.blkls", offset, path);
    if (system(command) != 0) {
        fprintf(stderr, "Error running blkls.\n");
        return 1;
    }

    // Step 2: Run strings to extract printable strings
    snprintf(command, sizeof(command), "strings -t d blkfile.blkls > blkfile.blkls.str");
    if (system(command) != 0) {
        fprintf(stderr, "Error running strings.\n");
        return 1;
    }

    // Step 3: Use grep to search for the specified word
    snprintf(command, sizeof(command), "grep \"%s\" blkfile.blkls.str", searchString);
    if (system(command) != 0) {
        printf("String not found.\n");
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <offset> <string_to_search>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    const char* searchString = argv[2];

    printf("**********************************************************************************************************************\n");
    printf("Displaying String Search Results:\n");
    int result = stringSearch(offset, searchString);
    printf("**********************************************************************************************************************\n");
    printf("\n");

    return result;
}
