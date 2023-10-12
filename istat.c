#include <stdio.h>
#include <stdlib.h>
FILE* file;
char path[100];

int istat(int offset, int inode) {
    	FILE* fpipe;
	char c = 0;
	char command[256];
	file = fopen("file_address.txt","r");
	if(fgets(path,sizeof(path),file) != NULL){
		snprintf(command, sizeof(command), "istat -o %d %s %d", offset, path, inode);
		
		fpipe = (FILE*)popen(command, "r");
		
		if(fpipe==NULL){
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
        printf("Usage: %s <offset>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    int inode = atoi(argv[2]);

    printf("**********************************************************************************************************************\n");
    printf("Displaying I-Node information:\n");
    int c = istat(offset,inode);
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}
