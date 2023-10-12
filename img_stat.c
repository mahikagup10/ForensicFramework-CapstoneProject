#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
FILE* file;
char path[100];

int img_stat(){
	FILE* fpipe;
	char c = 0;
	char command[256];
	file = fopen("file_address.txt","r");
	if(fgets(path,sizeof(path),file) != NULL){
		snprintf(command, sizeof(command), "img_stat %s", path);
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

int main(){

	printf("**********************************************************************************************************************\n");	
	printf("Displaying image information:\n");
	int a = img_stat();
	printf("**********************************************************************************************************************\n");
	printf("\n");
	return 0;

}
