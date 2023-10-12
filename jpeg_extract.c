#include <stdio.h>
#include <stdlib.h>
FILE* file;
char path[100];

int jpeg_extract(char folder[]) {
	FILE* fpipe;
	char c = 0;
	char command[256];
	file = fopen("file_address.txt","r");
	if(fgets(path,sizeof(path),file) != NULL){
		snprintf(command, sizeof(command), "foremost -t jpeg -i %s -o %s", path, folder);
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
        printf("Usage: %s <Folder>\n", argv[0]);
        return 1;
    }

    //char folder[50] = argv[1];

    printf("**********************************************************************************************************************\n");
    printf("A folder has been created with jpeg images.\n");
    int c = jpeg_extract(argv[1]);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
