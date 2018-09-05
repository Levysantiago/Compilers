#include <stdio.h>
#include <stdlib.h>

int verificaCadeia(int i, char *str);
char * error(int);

int main(int argc, char *argv[]){
	char terms[100];
	char ch;
	int i, pCount=0;

	while(scanf(" %[^\n]s", terms) != EOF){
		i=0;
		printf("\nAnalisando: %s\n", terms);
		if(terms[i] == 'x' && terms[i+1] == '\0'){
			printf("Cadeia aceita\n");
		}else if(terms[i] == '('){
			i++;
			i = verificaCadeia(i, terms);
			if(i < 0){
				printf(error(0));
			}else if(terms[i+1] != '\0'){
				printf(error(1));
			}
			else{
				printf("Cadeia aceita\n");
			}

		}else{
			printf(error(1));
		}
	}
}

int verificaCadeia(int i, char *str){
	if(str[i] == 'x'){
		while(str[i] == 'x' && str[i+1] == '+'){
			i += 2;
		}
		if(str[i] != 'x' && str[i+1] != ')' && str[i] != '('){
			return -1;
		}

		if(str[i] == 'x'){
			i++;
		}
		
		if(str[i] == ')'){
			return i;
		}
	}
	if(str[i] == '('){
		i++;
		i = verificaCadeia(i, str);
		if(i < 0){
			return -1;
		}
		i++;
		if(str[i] == '+'){
			i = verificaCadeia(++i, str);
			return i;
		}else if(str[i] != ')'){
			return -1;
		}
	}else{
		return -1;
	}

	return i;
}

char * error(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Repeticao de simbolos, omissao ou simbolos desconhecidos.\n";
			break;
		}

		case 1:{
			return "ERROR FOUND!: A cadeia que começa com '(' deve terminar com ')', assim como o inverso.\n";
			break;
		}
	}
}