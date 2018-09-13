#include <stdio.h>

char stack[512];
char arvoreANS[500];
char entrada[100];
int top = 0, entrPointer;

void push(char token);
char read();
char * erro(int op);
char pop();
char popIt(char token);
void printStack();
void printArvore();
void resetArvore();
void setFilhoEsquerdo(int index, char filho);
void setFilhoDireito(int index, char filho);
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
				pop();
				push('B'); push('A');
				setFilhoEsquerdo(nodeIndex, 'A');
				setFilhoDireito(nodeIndex, 'B');
			}
			if(stack[top] == 'A'){
				if(token == 'x' || token == 'y'){
					pop();
					push(token);
					/*Setando filho de A*/
					setFilhoEsquerdo(1, token);
				}else{
					printf(erro(0));
					continue;
				}
			}else if(stack[top] == 'B'){
				if(token == 'z' || token == 'w'){
					pop();
					push(token);
					/*Setando filho de B*/
					setFilhoEsquerdo(2, token);
				}else{
					printf(erro(1));
					continue;
				}
			}

			if(token == 'x' || token == 'y' || token == 'z' || token == 'w'){
				if(popIt(token) != ' '){
					goto q1;
				}else{
					printf(erro(2));
					continue;
				}
			}else if(token == '\0' && stack[top] == '$'){
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

char popIt(char token){
	if(stack[top] == token){
		return pop();
	}else{
		return ' ';
	}
}

char read(){
	return entrada[entrPointer++];
}

char * erro(int op){
	switch(op){
		case 0:{
			return "ERROR FOUND!: Cadeia precisa iniciar com x ou y.\n\n";
		}
		case 1:{
			return "ERROR FOUND!: Cadeia precisa finalizar com z ou w.\n\n";
		}
		case 2:{
			return "ERROR FOUND!: Cadeia precisa ter dois elementos.\n\n";
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

void setRaiz(char raiz){
	arvoreANS[0] = raiz;
}