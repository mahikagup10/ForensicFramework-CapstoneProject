#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
FILE* file;
char path[100];


int strings(){
	FILE* fpipe;
	char c = 0;
	char command[256];
	file = fopen("file_address.txt","r");
	if(fgets(path,sizeof(path),file) != NULL){
	snprintf(command, sizeof(command), "srch_strings %s", path);
		fpipe = (FILE*)popen(command, "r");
		
		if(fpipe==NULL){
			perror("Error opening pipe");
			exit(EXIT_FAILURE);
		}
		  FILE *outputFile = freopen("output.txt", "w", stdout);

	    if (outputFile == NULL) {
		perror("Error opening output file");
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


int main(){

	printf("**********************************************************************************************************************\n");
	printf("Output redirected to output.txt:\n");
	int b = strings();
	printf("**********************************************************************************************************************\n");
	printf("\n");
	return 0;

}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char path[] = "/home/kali/Downloads/Mantooth_raw.dd.raw";

int strings() {
    char command[256];
    snprintf(command, sizeof(command), "srch_strings %s > output.txt", path);

    if (system(command) == -1) {
        perror("Error running srch_strings");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main() {
    printf("**********************************************************************************************************************\n");
    printf("Output redirected to output.txt:\n");
    int b = strings();
    printf("**********************************************************************************************************************\n");
    printf("\n");
    return 0;
}*/
