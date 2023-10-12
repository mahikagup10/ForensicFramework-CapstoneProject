#include <stdio.h>
#include <stdlib.h>

char path[] = "/home/kali/Downloads/Mantooth_raw.dd.raw";

int fls(int offset) {
    FILE* fpipe;
    char c = 0;
    char command[256];
    printf("enteref");
    
    snprintf(command, sizeof(command), "fls -o %d -r %s", offset, path);
    fpipe = (FILE*)popen(command, "r");
    
    if(fpipe == NULL){
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }

    while(fread(&c, sizeof c, 1, fpipe)){
        printf("%c", c);
    }
    
    pclose(fpipe);
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <offset>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);

    printf("**********************************************************************************************************************\n");
    printf("Displaying Files and Directories:\n");
    int c = fls(offset);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
