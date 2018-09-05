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
		if(terms[i++] != 'x'){
			printf(error(0));
			continue;
		}

		while(terms[i] == 'y'){
			i++;
		};

		if(terms[i] == '\0'){
			printf(error(1));
			continue;
		}else if(terms[i] != 'z'){
			i++;
			if(terms[i] == '\0'){
				printf(error(1));
				continue;
			}else if(terms[i-1] != 'x'){
				printf(error(2));
				continue;
			}else{
				printf(error(0));
				continue;
			}
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
			return "ERROR FOUND!: A cadeia se inicia com 'x' e tem somente um 'x'.\n";
			break;
		}

		case 1:{
			return "ERROR FOUND!: Cadeia precisa terminar com 'z' e ter somente um 'z'.\n";
			break;
		}

		case 2:{
			return "ERROR FOUND!: Cadeia com simbolo desconhecido\n";
			break;
		}
	}
}