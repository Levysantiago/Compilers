#include "p-machine.h"

int main(int argc, char **argv){
	FILE *file = NULL;
	char inst[4];

	instCount = 0;

	/*Reading by a file*/
	if(argc == 2){
		file = fopen(argv[1], "r");
		if(file == NULL){
			printf("Erro ao abrir arquivo.\n");
			exit(-1);
		}

		while(fgets(inst, 4, file) != NULL){
			fscanf(file, "%d", &code[instCount].l);
			fscanf(file, "%d", &code[instCount].a);
			fgetc(file);
			code[instCount].f = getIntructionID(inst);
			instCount++;
		}

		fclose(file);
		file = NULL;
	/*Reading by user input*/
	}else{
		printf("Insira as instrucoes (END para finalizar a entrada)\n");

		while(1){
			scanf("\n %s", inst);
			if(strcmp(inst, "END") == 0){
				break;
			}else{
				scanf("%d %d", &code[instCount].l, &code[instCount].a);
				code[instCount].f = getIntructionID(inst);
				instCount++;
			}
		}
	}

	interpret();

	return 0;
}

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