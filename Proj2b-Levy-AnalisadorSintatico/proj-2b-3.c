#include <stdio.h>
#include <string.h>

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
			if(stack[top] == 'S'){
				token = entrada[ strlen(entrada) - 1 ];
				if( token == 'z' ){
					pop();
					push('B');
					setFilhoEsquerdo(nodeIndex, 'B');
				}else if( token == 'y' ){
					pop();
					push('A');
					setFilhoEsquerdo(nodeIndex, 'A');
				}else{
					printf(erro(0));
					continue;
				}
			}

			token = read();

			if(stack[top] == 'A' || stack[top] == 'B'){
				if(token == 'x'){
					nodeIndex = getFilhoEsqIndex(nodeIndex);
					setFilhoEsquerdo(nodeIndex, stack[top]);
					setFilhoDireito(nodeIndex, token);
					push(token);
				}else if(token == 'z' || token == 'y'){
					nodeIndex = getFilhoEsqIndex(nodeIndex);
					setFilhoEsquerdo(nodeIndex, token);
					pop();
				}
			}
			if(stack[top] == 'x'){
				pop();
				goto q1;
			}
			if(stack[top] == '$' && entrada[entrPointer] == '\0'){
				printArvore();
			}else{
				printf(erro(1));
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
			return "ERROR FOUND!: Cadeia deve terminar com 'z' ou 'y'.\n\n";
		}
		case 1:{
			return "ERROR FOUND!: Apos 'z' e 'y', nao são aceitos mais simbolos.\n\n";
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