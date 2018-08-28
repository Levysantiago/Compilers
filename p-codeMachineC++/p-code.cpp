/*Código usado como base para padronizar a implementação do p-code. Este código foi implementado por outra fonte,
acesso em: cpp.sh/9nsyz*/

// p-code.cpp : 
//
// C conventions
// 0 == FALSE
//
#include <stdio.h>

#define levmax 3
#define amax 2047

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};

typedef struct tinstruction {
     fct    f;
     int    l; // l: 0..levmax; // Level buffer
     int    a; // a: 0..amax;   // Address buffer
}instruction;

instruction code[2048];

//procedure interpret;
// const stacksize = 500;

#define stacksize 5012

 // p, b, t: integer; {program-, base-, topstack-registers}
 int p, // program-register
     b, // base-register
     t; // topstack-register
 
instruction i;            //: instruction; {instruction register}
int         s[stacksize]; //: array [1..stacksize] of integer; {datastore}

int base(int l){ //l: integer)
 int b1; //

 b1 = b; // {find base l levels down}
 while (l > 0) {
    b1 = s[b1];
    l  = l - 1;
 }
 return b1;
}//end-int-base

// Determina se seu argumento é impar
int odd(int x){ return (  ((x%2)==1) ); }

void pcodevhw(){ // begin 
 printf("\n start pl/0");
 printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ===");
 t = -1; // topstack-register
 b = 0; // base-register
 p = 0; // program-register
 
 // OBS: s[0] must not be used
 s[1] = 0; 
 s[2] = 0; 
 s[3] = 0;
 
 do {
  i = code[p]; 
  //printf("\n %3d %3d %3d - %3d %3d %3d", t, b, p, i.f, i.l, i.a);
  printf("\n %3d %3d %3d   ", t, b, p);
  p = p + 1;
 // switch case i.f-BEGIN
  switch  (i.f) { // with i do case f of
    case LIT : { t = t + 1; s[t] = i.a; printf("LIT %3d %3d", i.l, i.a); } break;
    case OPR :
               printf("OPR %3d %3d", i.l, i.a);
//             switch case i.a-BEGIN
               switch (i.a) { // case a of {operator}
                 case  0: { // return
                            t = b - 1; 
                            p = s[t + 3]; 
                            b = s[t + 2];
                          }
                          break;
         
                 case  1: { //
                            s[t] = -s[t];
                          }
                          break;
         
                 case  2: { //  ADD     : PUSH( POP()+POP() )
                            t    = t - 1; 
                            s[t] = s[t] + s[t + 1];
                          }
                          break;
         
                 case  3: { // SUBSTRACT: PUSH( POP()-POP() )
                            t    = t - 1; 
                            s[t] = s[t] - s[t + 1];
                          }
                          break;
         
                 case  4: { // MULTIPLY: PUSH( POP()*POP() )
                            t    = t - 1; 
                            s[t] = s[t] * s[t + 1];
                          }
                          break;
         
                 case  5: { // DIVIDE  : PUSH( POP()/POP() )
                            t    = t - 1; 
                            s[t] = s[t] / s[t + 1];
                          }
                          break;
         
                 case  6: { // 
                            s[t] = odd(s[t]); //s[t] = ord(odd(s[t]));
                          }
                          break;
         
                 case  8: { // EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] == s[t + 1]);
                          }
                          break;
         
                 case  9: { // NOT.EQUAL
                            t    = t - 1; 
                            s[t] = (s[t] != s[t + 1]);
                          }
                          break;
         
                 case 10: { // LESS THAN
                            t    = t - 1; 
                            s[t] = (s[t] < s[t + 1]);
                          }
                          break;
         
                 case 11: { // GREATER EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] >= s[t + 1]);
                          }
                          break;
         
                 case 12: { // GREATER THAN
                            t = t - 1; 
                            s[t] = (s[t] > s[t + 1]);
                          }
                          break;
         
                 case 13: { // LESS EQUAL THAN
                            t    = t - 1; 
                            s[t] = (s[t] <= s[t + 1]);
                          }
                          break;
               } // end;
//         switch case i.a-END
           break;

   case LOD : { // LOAD
                printf("LOD %3d %3d", i.l, i.a);
                t    = t + 1; 
                s[t] = s[base(i.l) + i.a];
              }
              break;

   case STO : { // STORE
                printf("STO %3d %3d", i.l, i.a);
                s[base(i.l)+i.a] = s[t]; 
                t            = t - 1;
              }
              break;

   case CAL :
              { // {generate new block mark}
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = base(i.l); 
                s[t + 2] = b; 
                s[t + 3] = p;
                b        = t + 1; 
                p        = i.a;
              }
              break;

   case INT : t = t + i.a;printf("INT %3d %3d", i.l, i.a); break;
   case JMP : p = i.a;    printf("JMP %3d %3d", i.l, i.a); break;
   case JPC : if (s[t] == 1) { p = i.a; }  t = t - 1; printf("JPC %3d %3d", i.l, i.a); break;
  } // end {with, case}
  // switch case i.f-END
  
  // print stack
  printf("      s[] : ");
  for (int h=0; h<=t; h++) { printf(" %3d", s[h]); }
 } while ( p != 0 );

 printf("\n === === ===   === === ===             === === === === === === === === === === === === === === ==="); 
 printf("\n t   b   p     f   l   a                 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14");
 printf("\n end pl/0");
}//end-void-pcmachine() {interpret};

int main(){

  /*Um contador para determinar o próximo índice do vetor "code"
  (próxima linha da implementação p-code)*/
  int i = 0;
  /*Vetores usados para definir o conteúdo das matrizes,
  usado somente no momento do preenchimento das matrizes.*/
  int A[6] = {0,0,0,1,1,1};
  int B[6] = {0,1,0,1,0,1};

	// Aqui vc preenche as instrucoes no vetor code
  /*Preenchendo matriz A*/
  code[ i].f = INT; code[ i].l = 0; code[ i++].a = 23;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[0];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 3;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[1];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 4;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[2];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 5;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[3];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 6;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[4];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 7;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = A[5];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 8;

  /*Preenchendo matriz B*/
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[0];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 9;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[1];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 10;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[2];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 11;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[3];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 12;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[4];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 13;
  code[ i].f = LIT; code[ i].l = 0; code[ i++].a = B[5];
  code[ i].f = STO; code[ i].l = 0; code[ i++].a = 14;

  code[ i].f = CAL; code[ i].l = 0; code[ i++].a = 29; // Chamando função de multiplicação para C = A * B
  code[ i].f = CAL; code[ i].l = 0; code[ i++].a = 79; // Chamando função de multiplicação para D = (C * C)
  code[ i].f = CAL; code[ i].l = 0; code[ i++].a = 113; // Chamando função de soma para D = D + C
  code[ i].f = JMP; code[ i].l = 0; code[ i++].a = 131; // Pulando para o retorno final

  /*Iniciando multiplicação de A com B e armazenando em C*/
  code[ i].f = INT; code[ i].l = 0; code[ i++].a = 3; // linha 29
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 3;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 9;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 11;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 5;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 13;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 15;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 3;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 10;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 12;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 5;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 14;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 16;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 6;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 9;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 7;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 11;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 8;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 13;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 17;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 6;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 10;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 7;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 12;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 8;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 14;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 18;

  /*Retorna para a main*/
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 0;

  /*Iniciando cálculo de C * C e armazenando em D*/
  code[ i].f = INT; code[ i].l = 1; code[ i++].a = 3; // linha 79
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 15;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 15;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 16;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 17;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 19;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 15;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 16;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 16;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 18;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 20;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 17;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 15;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 18;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 17;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 21;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 17;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 16;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 18;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 18;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 4;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 22;

  /*Retorna para a main*/
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 0;

  /*Realizando a soma de D (C * C) com C e armazenando em D*/
  code[ i].f = INT; code[ i].l = 1; code[ i++].a = 3; // linha 113
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 15;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 19;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 19;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 16;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 20;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 20;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 17;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 21;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 21;

  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 18;
  code[ i].f = LOD; code[ i].l = 1; code[ i++].a = 22;
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 2;
  code[ i].f = STO; code[ i].l = 1; code[ i++].a = 22;

  /*Retorna para a main*/
  code[ i].f = OPR; code[ i].l = 1; code[ i++].a = 0;  

  /*RETORNO FINAL*/
  code[ i].f = OPR; code[ i].l = 0; code[ i++].a = 0;  // linha 131

	// Aqui vc chama a P-code machine para interpretar essas instrucoes
	pcodevhw();

	return 0;
}