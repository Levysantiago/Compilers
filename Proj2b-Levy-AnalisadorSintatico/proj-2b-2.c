#include <stdio.h>

char stack[512];
char arvoreANS[500];
char entrada[100];
int top = 0, entrPointer;

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
			if(stack[top] == 'S'){
				if(token != 'x'){
					printf(erro(2));
					continue;
				}
				pop();
				push('A'); push('x');
				setFilhoEsquerdo(nodeIndex, 'A');
				setFilhoDireito(nodeIndex, 'x');
			}else if(stack[top] == 'y'){
				pop();
			}

			if(stack[top] == 'x' && token == 'x'){
				pop();
				if(entrada[entrPointer] == '\0'){
					printf(erro(1));
					continue;
				}
				goto q1;
			}else if(token == 'y' && stack[top] == 'A'){
				pop();
				push('A'); push(token);
				nodeIndex = getFilhoEsqIndex(nodeIndex);
				setFilhoEsquerdo(nodeIndex, 'A');
				setFilhoDireito(nodeIndex, 'y');
				if(entrada[entrPointer] == '\0'){
					printf(erro(1));
					continue;
				}
				goto q1;
			}else if(token == 'z' && stack[top] == 'A'){
				pop();
				nodeIndex = getFilhoEsqIndex(nodeIndex);
				setFilhoEsquerdo(nodeIndex, 'z');
				goto q2;
			}else{
				printf(erro(0));
				continue;
			}

		q2:
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
			return "ERROR FOUND!: Entre 'x' e 'z' só pode existir 'y'.\n\n";
		}
		case 1:{
			return "ERROR FOUND!: Cadeia precisa finalizar com 'z' e somente um 'z'.\n\n";
		}
		case 2:{
			return "ERROR FOUND!: Cadeia precisa iniciar com 'x' e somente um 'x'.\n\n";
		}
	}
}

void printStack(){
	for(int i=0; i<top ; i++){
		printf("%c ", stack[i]);
	}
	printf("\n");
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

void resetArvore(){
	for(int i=0; i < 500; i++){
		arvoreANS[i] = ' ';
	}
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