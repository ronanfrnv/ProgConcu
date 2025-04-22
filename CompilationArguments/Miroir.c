#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	printf("La commade a  %d arguments",argc);
	printf("\n");
	for(int i = 1 ; i<argc;++i){
		int temp = strlen(argv[i]);
		printf(" ");
		for (int j = temp ;j>=0 ; --j){
			printf("%c",argv[i][j]);
		}
	}
	printf("\n");
	return 0;
}
