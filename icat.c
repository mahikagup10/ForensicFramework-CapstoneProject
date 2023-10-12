#include <stdio.h>
#include <stdlib.h>

char path[] = "/home/kali/Desktop/capstone/MantoothImage.001";

int icat(int offset, int inode) {
    	FILE* fpipe;
	char c = 0;
	char command[256];
	
	snprintf(command, sizeof(command), "icat -o %d %s %d", offset, path, inode);
	
	fpipe = (FILE*)popen(command, "r");
	
	if(fpipe==NULL){
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
    if (argc != 3) {
        printf("Usage: %s <offset>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    int inode = atoi(argv[2]);

    printf("**********************************************************************************************************************\n");
    printf("Displaying General contents of the file:\n");
    int c = icat(offset,inode);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
