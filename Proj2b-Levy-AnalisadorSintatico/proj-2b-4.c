#include <stdio.h>

char stack[512];
char arvoreANS[500];
char entrada[100];
int top, entrPointer;

void push(char token);
char read();
char * erro(int op);
char pop();
void printStack();
void printArvore();
void resetArvore();
void setFilhoEsquerdo(int index, char filho);
void setFilhoDireito(int index, char filho);
int getFilhoEsqIndex(int index);
void setRaiz(char raiz);

int main(){
	char token;
	int nodeIndex;

	while(scanf(" %[^\n]s", entrada) != EOF){
		entrPointer = 0;
		top = -1;
		nodeIndex = 0;
		resetArvore();

		printf("Analisando %s...\n", entrada);

		q0:
			push('$');
			push('S');
			setRaiz('S');

		q1:
			token = read();
			if(stack[top] == 'S' && token == 'x'){
				pop();
				push('x');
				setFilhoEsquerdo(nodeIndex, 'x');
			}else{
				printf(erro(0));
				continue;
			}

			token = read();

			if(token == 'x'){
				push('A');
				setFilhoEsquerdo(nodeIndex, 'A');
				setFilhoDireito(nodeIndex, 'x');
				
				pop();
				push('x');
				nodeIndex = getFilhoEsqIndex(nodeIndex);
				setFilhoEsquerdo(nodeIndex, 'x');

				token = read();
			}else if(token != '\0'){
				printf(erro(1));
				continue;
			}

			while(stack[top] == 'x'){
				pop();
			}

			if(stack[top] == '$' && token == '\0'){
				printArvore();
			}else{
				printf(erro(2));
			}
	}
}

void push(char token){
	stack[++top] = token;
}

char pop(){
	return stack[--top];
}

char read(){
	return entrada[entrPointer++];
}

char * erro(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Cadeia precisa iniciar com 'x'.\n\n";
		}
		case 1:{
			return "ERROR FOUND!: O segundo simbolo precisa ser 'x'.\n\n";
		}
		case 2:{
			return "ERROR FOUND!: A cadeia tem mais de dois simbolos.\n\n";
		}
	}
}

void printStack(){
	for(int i=0; i<top+1 ; i++){
		printf("%c ", stack[i]);
	}
	printf("\n");
}

void resetArvore(){
	for(int i=0; i < 500; i++){
		arvoreANS[i] = ' ';
	}
}

void printArvore(){
	printf("Arvore de analise\n");
	for(int i=0; i < 500; i++){
		if(arvoreANS[i] != ' '){
			printf("%c\n", arvoreANS[i]);
		}
	}
	printf("\n");
}

void setFilhoEsquerdo(int index, char filho){
	arvoreANS[2*index + 1] = filho;
}

void setFilhoDireito(int index, char filho){
	arvoreANS[2*index + 2] = filho;
}

int getFilhoEsqIndex(int index){
	return 2*index + 1;
}

void setRaiz(char raiz){
	arvoreANS[0] = raiz;
}