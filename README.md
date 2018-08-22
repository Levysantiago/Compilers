# p-code-machine
This repository is used for Compilers subject. Here is presented a p-code machine developed in C language. The code was based on a [Pascal code](https://en.wikipedia.org/wiki/P-code_machine). A p-code-machine (portable code machine) is a virtual machine designed to execute p-code (the assembly language of a hypothetical CPU).

## Commands
These are the commands accepted by the p-code-machine, you can find more about it [here](http://blackmesatech.com/2011/12/pl0/pl0.xhtml).
- **LIT 0, a :** load constant a;
- **OPR 0, a :** execute operation a (13 operations: RETURN, 5 math functions, and 7 comparison functions);
- **LOD l, a :** load variable a from level l;
- **STO l, a :** store variable a at level l;
- **CAL l, a :** call procedure a at level l;
- **INT 0, a :** increment t-register by a;
- **JMP 0, a :** jump to a;
- **JPC 0, a :** jump conditional to a (if '0' jump, else don't jump).

This table shows the meaning of all 13 OPR operations:

| code  | Symbol | Semantics |
| --- | --- | --- |
| 0  | Return  | Return from a subroutine.  |
| 1  | Negate  | Negate the value on the top of the stack (i.e. multiply by -1).  |
| 2  | Add  | x=pop();y=pop();push(y+x).  |
| 3  | Subtract  | x=pop();y=pop();push(y-x).  |
| 4  | Multiply  | x=pop();y=pop();push(y*x).  |
| 5  | Divide  | x=pop();y=pop();push(y/x).  |
| 6  | Odd?  | Test the value at the top of the stack to see if it's odd or not.  |
| 7  | == | x=pop();y=pop();push(y==x). |
| 8  | <> | x=pop();y=pop();push(y<>x). |
| 9  | < | x=pop();y=pop();push(y<x). |
| 10  | >= | x=pop();y=pop();push(y>=x). |
| 11  | > | x=pop();y=pop();push(y>x). |
| 12  | <= | x=pop();y=pop();push(y<=x). |

## Getting Started
Here are some instructions that will help you how to run this code in your machine for development and testing purposes.

### Prerequisites
You'll need to install gcc compiler before you get forward.

### Compiling
To compile the code with gcc in your terminal just execute:
```
$ gcc main.c -o machine
```

### Executing
You can execute the code setting a a file as program parameter, or by writing the p-code directally on your terminal.

#### Executing the program on terminal
```
$ ./machine
```

#### Executing the program with a file
```
$ ./machine exemplos/fibonacciRec5
```

### Running the tests
There is some p-codes in "examples" directory that you can use to test.

#### Calculating 2² + 3 x 2 + 1
```
$ ./machine examples/expression

INT 0 4
LIT 0 1
STO 0 0
LIT 0 2
STO 0 1
LIT 0 3
STO 0 2
LOD 0 1
LOD 0 1
OPR 0 4
LOD 0 2
LOD 0 1
OPR 0 4
LOD 0 0
OPR 0 2
OPR 0 2

CONFIGURATION:

Instruction 	 Level    Argument    StackPtr     ProgCounter     Stack

   INT             0          4          0             1 	   0 0 0 0 
   LIT             0          1          1             2 	   0 0 0 0 1 
   STO             0          0          0             3 	   1 0 0 0 
   LIT             0          2          2             4 	   1 0 0 0 2 
   STO             0          1          0             5 	   1 2 0 0 
   LIT             0          3          3             6 	   1 2 0 0 3 
   STO             0          2          0             7 	   1 2 3 0 
   LOD             0          1          2             8 	   1 2 3 0 2 
   LOD             0          1          2             9 	   1 2 3 0 2 2 
   OPR             0          4          4            10 	   1 2 3 0 4 
   LOD             0          2          3            11 	   1 2 3 0 4 3 
   LOD             0          1          2            12 	   1 2 3 0 4 3 2 
   OPR             0          4          6            13 	   1 2 3 0 4 6 
   LOD             0          0          1            14 	   1 2 3 0 4 6 1 
   OPR             0          2          7            15 	   1 2 3 0 4 7 
   OPR             0          2         11            16 	   1 2 3 0 11 

OUTPUT: 11
```

#### Fibonacci of 5
```
./machine examples/fibonacci_5

INT 0 3
LIT 0 1
STO 0 0
LIT 0 1
STO 0 1
LIT 0 3
STO 0 2
LOD 0 0
LOD 0 1
OPR 0 2
LOD 0 1
STO 0 0
STO 0 1
LIT 0 5
LOD 0 2
OPR 0 11
JPC 0 22
LOD 0 2
LIT 0 1
OPR 0 2
STO 0 2
JMP 0 7
LOD 0 1
OPR 0 0

CONFIGURATION:

Instruction 	 Level    Argument    StackPtr     ProgCounter     Stack

   INT             0          3          0             1 	   0 0 0 
   LIT             0          1          1             2 	   0 0 0 1 
   STO             0          0          0             3 	   1 0 0 
   LIT             0          1          1             4 	   1 0 0 1 
   STO             0          1          0             5 	   1 1 0 
   LIT             0          3          3             6 	   1 1 0 3 
   STO             0          2          3             7 	   1 1 3 
   LOD             0          0          1             8 	   1 1 3 1 
   LOD             0          1          1             9 	   1 1 3 1 1 
   OPR             0          2          2            10 	   1 1 3 2 
   LOD             0          1          1            11 	   1 1 3 2 1 
   STO             0          0          2            12 	   1 1 3 2 
   STO             0          1          3            13 	   1 2 3 
   LIT             0          5          5            14 	   1 2 3 5 
   LOD             0          2          3            15 	   1 2 3 5 3 
   OPR             0         11          1            16 	   1 2 3 1 
   JPC             0         22          3            17 	   1 2 3 
   LOD             0          2          3            18 	   1 2 3 3 
   LIT             0          1          1            19 	   1 2 3 3 1 
   OPR             0          2          4            20 	   1 2 3 4 
   STO             0          2          4            21 	   1 2 4 
   JMP             0          7          4             7 	   1 2 4 
   LOD             0          0          1             8 	   1 2 4 1 
   LOD             0          1          2             9 	   1 2 4 1 2 
   OPR             0          2          3            10 	   1 2 4 3 
   LOD             0          1          2            11 	   1 2 4 3 2 
   STO             0          0          3            12 	   2 2 4 3 
   STO             0          1          4            13 	   2 3 4 
   LIT             0          5          5            14 	   2 3 4 5 
   LOD             0          2          4            15 	   2 3 4 5 4 
   OPR             0         11          1            16 	   2 3 4 1 
   JPC             0         22          4            17 	   2 3 4 
   LOD             0          2          4            18 	   2 3 4 4 
   LIT             0          1          1            19 	   2 3 4 4 1 
   OPR             0          2          5            20 	   2 3 4 5 
   STO             0          2          5            21 	   2 3 5 
   JMP             0          7          5             7 	   2 3 5 
   LOD             0          0          2             8 	   2 3 5 2 
   LOD             0          1          3             9 	   2 3 5 2 3 
   OPR             0          2          5            10 	   2 3 5 5 
   LOD             0          1          3            11 	   2 3 5 5 3 
   STO             0          0          5            12 	   3 3 5 5 
   STO             0          1          5            13 	   3 5 5 
   LIT             0          5          5            14 	   3 5 5 5 
   LOD             0          2          5            15 	   3 5 5 5 5 
   OPR             0         11          0            16 	   3 5 5 0 
   JPC             0         22          5            22 	   3 5 5 
   LOD             0          1          5            23 	   3 5 5 5 

OUTPUT: 5
```