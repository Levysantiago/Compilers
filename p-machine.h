#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define levmax 3
#define stacksize 500

typedef enum fct{LIT, OPR, LOD, STO, CAL, INT, JMP, JPC} fct;

char * instructions[] = { "LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"};

typedef struct instruction{
	fct f;
	int l;
	int a;
} instruction;

/*FUNCTIONS*/
int getIntructionID(char *inst);
int base(int l);
void interpret();

/*
	p: program-register
	b: base-register
	t: topstack-register
*/
int p, b, t, instCount;

/*i: instruction-register*/
instruction i;

instruction code[stacksize];

/*s: datastore*/
int s[stacksize] = {-1};

int getIntructionID(char *inst){
	int id;
	for (id = 0; id<8;id++){
		if(strcmp(inst, instructions[id]) == 0){
			return id;
		}
	}
	return -1;
}

char * getInstructionByID(int id){
	if(id < 8){
		return instructions[id];
	}
	return "***";
}

int base(int l){
	int b1 = b;
	while(l > 0){
		b1 = s[b1];
		l = l - 1;
	}

	return b1;
}

void interpret(){	
t = p = 0;
	b = 1;
	s[1] = s[2] = s[3] = 0;

	printf("\n\nCONFIGURATION:\n\nInstruction \t Level    Argument    StackPtr     ProgCounter     Stack\n\n");

	do{
		i = code[p];
		p++;

		switch(i.f){
			case LIT:{
				t++;
				s[t] = i.a;
				break;
			}
			case OPR:{
				/*Is an operator*/
				switch(i.a){
					case 0:{ /*Return*/
						t = b - 1;
						p = s[t + 3];
						b = s[t + 2];
						break;
					} 
					case 1:{
						s[t] = ~s[t];
						break;
					}
					case 2:{
						t--;
						s[t] = s[t] + s[t + 1];
						break;
					}
					case 3:{
						t--;
						s[t] = s[t] - s[t + 1];
						break;
					}
					case 4:{
						t--;
						s[t] = s[t] * s[t + 1];
						break;
					}
					case 5:{
						t--;
						s[t] = s[t] / s[t + 1];
						break;
					}
					case 6:{
						s[t] = (s[t] % 2 == 1);
						break;
					}
					case 7:{
						t--;
						s[t] = (s[t] == s[t + 1]);
						break;
					}
					case 8:{
						t--;
						s[t] = (s[t] != s[t + 1]);
						break;
					}
					case 9:{
						t--;
						s[t] = (s[t] < s[t + 1]);
						break;
					}
					case 10:{
						t--;
						s[t] = (s[t] >= s[t + 1]);
						break;
					}
					case 11:{
						t--;
						s[t] = (s[t] > s[t + 1]);
						break;
					}
					case 12:{
						t--;
						s[t] = (s[t] <= s[t + 1]);
						break;
					}
				} /*End of operator switch*/
				break;
			}
			case LOD:{
				t++;
				s[t] = s[base(i.l) + i.a];
				break;
			}
			case STO:{
				s[base(i.l) + i.a] = s[t];
				t--;
				break;
			}
			case CAL:{
				s[t + 1] = base(i.l);
				s[t + 2] = b;
				s[t + 3] = p;
				b = t + 1;
				p = i.a;
				break;
			}
			case INT:{
				t += i.a;
				break;
			}
			case JMP:{
				p = i.a;
				break;
			}
			case JPC:{
				if(s[t] == 0){
					p = i.a;
				}
				t--;
				break;
			}
			default:{
				printf("\nInstrucao nao reconhecida.\n");
				exit(-1);
				break;
			}
		} /*End of Switch*/

		printf("%6s %13d %10d %10d %13d \t   ", getInstructionByID(i.f),i.l, i.a, s[t], p);

		for (int aux = b; aux<t+1;aux++){
			printf("%d ", s[aux]);
		}
		printf("\n");
	}while(p < instCount);
	printf("\n");

	printf("OUTPUT: %d\n\n", s[t]);
}