#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main (int argc, char* argv[]){
	for(int j = 1 ; j< argc;++j){
		if (isdigit(argv[j])){
			printf("\nArgument validé\n");
		}else{
		printf("\n %c n'est un chiffre.\n", argv[j]);
		}
	}
}
