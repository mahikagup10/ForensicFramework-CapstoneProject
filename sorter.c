#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

FILE* file;
char path[100];

int sorter(int offset) {
    FILE* fpipe;
    char c = 0;
    char command[256];
    
    // Create the 'sorted_files' directory if it doesn't exist
    const char* directory_name = "sorted_files";
    if (mkdir(directory_name, 0777) == -1) {
        if (errno != EEXIST) {
            perror("Error creating 'sorted_files' directory");
            exit(EXIT_FAILURE);
        }
    }
    
    file = fopen("file_address.txt","r");
    if(fgets(path,sizeof(path),file) != NULL){
	    snprintf(command, sizeof(command), "sorter -o %d -s -d  sorted_files %s", offset, path);
	    fpipe = (FILE*)popen(command, "r");
	    
	    if(fpipe == NULL){
		perror("Error opening pipe");
		exit(EXIT_FAILURE);
	    }

	    while(fread(&c, sizeof c, 1, fpipe)){
		printf("%c", c);
	    }
	    
	    pclose(fpipe);
    }
    fclose(file); 
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <offset>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);

    printf("**********************************************************************************************************************\n");
    printf("Files are being categorized:\n");
    int c = sorter(offset);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
