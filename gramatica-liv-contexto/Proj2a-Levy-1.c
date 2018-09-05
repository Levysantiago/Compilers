#include <stdio.h>
#include <stdlib.h>

char * error(int);

int main(int argc, char *argv[]){
	char terms[100];
	char ch;
	int i;

	while(scanf(" %[^\n]s", terms) != EOF){
		printf("\nAnalisando: %s\n", terms);
		i=0;
		if(terms[i] != 'x' && terms[i] != 'y'){
			printf(error(0));
			continue;
		}
		i++;
		if(terms[i] != 'w' && terms[i] != 'z'){
			printf(error(1));
			continue;
		}
		i++;
		if(terms[i] != '\0'){
			printf(error(2));
		}
	}
}

char * error(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Cadeia só pode iniciar com 'x' ou 'y'.\n";
		}

		case 1:{
			return "ERROR FOUND!: Cadeia precisa finalizar com 'z' ou 'w'.\n";
		}

		case 2:{
			return "ERROR FOUND!: A cadeia só pode ter dois símbolos.\n";
		}
	}
}