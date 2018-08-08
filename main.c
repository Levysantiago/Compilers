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

