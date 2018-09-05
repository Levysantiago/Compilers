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
		while(terms[i] == 'x'){
			i++;
		}

		if(terms[i] != 'y' && terms[i] != 'z'){
			printf(error(0));
		}else{
			i++;
			if(terms[i] != '\0'){
				printf(error(1));
			}
		}
	}
}

char * error(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Cadeia com simbolo desconhecido.\n";
			break;
		}

		case 1:{
			return "ERROR FOUND!: Cadeia deve terminar com 'z' ou 'y'.\n";
			break;
		}
	}
}