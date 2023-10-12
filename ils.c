#include <stdio.h>
#include <stdlib.h>
FILE* file;
char path[100];

int ils(int offset) {
	FILE* fpipe;
	char c = 0;
	char command[256];
	file = fopen("file_address.txt","r");
	if(fgets(path,sizeof(path),file) != NULL){
		snprintf(command, sizeof(command), "ils -f ntfs -o %d %s", offset, path);
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
    printf("Displaying Inode Information:\n");
    int c = ils(offset);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
