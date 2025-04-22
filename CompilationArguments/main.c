#include <stdio.h>

int main(int argc,char * argv[]){

	printf("\n %s a reçu %d arguments(s):\n",argv[0],argc);
	for (int i=1; i<argc; ++i)
		puts(argv[i]);
	return 0;

}
