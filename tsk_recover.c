#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
FILE* file;
char path[100];

int recover(int offset, const char* dire) {
    FILE* fpipe;
    char c = 0;
    char command[256];

    file = fopen("file_address.txt","r");
    if(fgets(path,sizeof(path),file) != NULL){
	    // Check that dire is not NULL
	    if (dire == NULL) {
		fprintf(stderr, "Output file not specified.\n");
		return EXIT_FAILURE;
	    }
		
	    // Print the directory to verify it
	    printf("Output file: %s\n", dire);

	    snprintf(command, sizeof(command), "tsk_recover -e -o %d %s '%s'", offset, path, dire);
	    
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
    if (argc != 3) {
        printf("Usage: %s <offset> <output_directory>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    const char* dire = argv[2];

    printf("**********************************************************************************************************************\n");
    printf("Recovered files get stored in your local directory\n");
    int result = recover(offset, dire);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
