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