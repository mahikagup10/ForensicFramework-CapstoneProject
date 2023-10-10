#include<stdio.h>
#include<strings.h>
#include<stdlib.h>

char path[] = "/home/mahika/Downloads/CapstoneFramework/Mantooth_raw.dd.raw";


int mmls(){
	FILE* fpipe;
	char c = 0;
	char command[256];
	snprintf(command, sizeof(command), "mmls %s", path);
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


int main(){

	printf("**********************************************************************************************************************\n");
	printf("Displaying Partition Layout of Volume System:\n");
	int b = mmls();
	printf("**********************************************************************************************************************\n");
	printf("\n");
	return 0;

}
