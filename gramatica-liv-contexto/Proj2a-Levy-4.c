#include <stdio.h>
#include <stdlib.h>

char * error(int);

int main(int argc, char *argv[]){
	char terms[100];
	char ch;
	int i;

	while(scanf(" %[^\n]s", terms) != EOF){
		i=0;
		printf("\nAnalisando: %s\n", terms);
		if(terms[i] != 'x'){
			printf(error(0));
			continue;
		}else{
			i++;
			if(terms[i] != 'x'){
				if(terms[i] != '\0'){
					printf(error(0));
					continue;
				}
			}else{
				i++;
				if(terms[i] != '\0'){
					printf(error(2));
					continue;
				}
			}
		}
	}
}

char * error(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Cadeia deve iniciar com 'x' e terminar com 'x'.\n";
		}

		case 2:{
			return "ERROR FOUND!: Cadeia precisa ter 1 ou 2 elementos.\n";
		}
	}
}