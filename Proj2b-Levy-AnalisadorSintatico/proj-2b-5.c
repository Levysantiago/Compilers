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
int setFilhoEsquerdo(int index, char filho);
int setFilhoMeio(int index, char filho);
int setFilhoDireito(int index, char filho);
void setRaiz(char raiz);

int main(){
	char token;
	int noIndexA, noIndexB, noIndexC;

	while(scanf(" %[^\n]s", entrada) != EOF){
		entrPointer = 0;
		top = -1;
		noIndexA = 0;
		noIndexB = 0;
		noIndexC = 0;
		resetArvore();

		printf("Analisando %s...\n", entrada);

		q0:
			push('$');
			push('A');
			setRaiz('A');

		q1:
			token = read();
			if(stack[top] == 'A'){
				if(token == 'x'){
					pop();
					push('x');
					setFilhoEsquerdo(noIndexA, 'x');
				}else if(token == '('){
					pop();
					push(')');push('B');push('(');
					setFilhoEsquerdo(noIndexA, '(');
					noIndexB = setFilhoMeio(noIndexA, 'B');
					setFilhoDireito(noIndexA, ')');
				}else{
					printf(erro(0));
					continue;
				}
			}

			if(stack[top] == '(' || stack[top] == 'x'){
				pop();
				goto q2;
			}

		q2:
			if(stack[top] == 'B'){
				pop();
				push('C'); push('A');
				noIndexA = setFilhoEsquerdo(noIndexB, 'A');
				noIndexC = setFilhoMeio(noIndexB, 'C');
				goto q1;
			}else if(stack[top] == ')'){
				while(entrada[entrPointer] == ')'){					
					token = read();
					pop();
				}
			}else if(stack[top] == 'C'){
				pop();
				goto q3;
			}

		q3:
			token = read();
			if(token == '+'){
				push('A'); push('+');
				setFilhoEsquerdo(noIndexC, '+');
				noIndexA = setFilhoMeio(noIndexC, 'A');
				pop();
				goto q1;
			}else if(token == ')' && stack[top] == ')'){
				pop();
				goto q3;
			}else if(token == '\0' && stack[top] == '$'){
				printf("OK\n");
				printArvore();
			}else{
				printf(erro(0));
				continue;
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
			return "ERROR FOUND!: A cadeia possui simbolos desorganizados.\n\n";
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

int setFilhoEsquerdo(int index, char filho){
	int id = 2*index + 1;
	arvoreANS[id] = filho;
	return id;
}

int setFilhoMeio(int index, char filho){
	int id = 2*index + 2;
	arvoreANS[id] = filho;
	return id;
}

int setFilhoDireito(int index, char filho){
	int id = 2*index + 3;
	arvoreANS[id] = filho;
	return id;
}

void setRaiz(char raiz){
	arvoreANS[0] = raiz;
}