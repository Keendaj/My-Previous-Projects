#include "..\FixLib\FixLib.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST1_SIZE 6
#define TEST2_SIZE 4
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#pragma warning(disable:4996)


typedef struct
{
	fixed_t (*myfunc)(fixed_t a);
	char name[20];
} test1;

typedef struct
{
	fixed_t(*myfunc)(fixed_t a, fixed_t b);
	char name[20];
} test2;

int main() {
	printf("-------------------------------------------------------------------------\n");
	printf("|                 Tests for my static library                           |\n");
	printf("-------------------------------------------------------------------------\n");
	test1 ListWithFuncs1[TEST1_SIZE] = { {FixNegate, "Negate"}, {FixReciprocal, "Reciprocal"}, {FixAbs,"Abs"},{FixRound,"Round"},{FixCeil,"Ceil"},{FixFloor,"Floor"} };
	test2 ListWithFuncs2[TEST2_SIZE] = { {FixAdd, "Add"}, {FixSub, "Sub"}, {FixMul,"Mul"},{FixDiv,"Div"}};
	double a = 20.35, b = 14.5;
	int c = 10.5;
	char str[20];
	char* test_str;

	fixed_t a1 = FixFromDouble(a);
	fixed_t b1 = FixFromDouble(b);
	fixed_t c1 = FixFromInt(c);
	fixed_t k;
	int new_c = FixAsInt(c1);
	double new_a = FixAsDouble(a1);

	for (int i = 0; i < TEST1_SIZE; i++) {
		k = ListWithFuncs1[i].myfunc(a1);
		printf("%s: %d.%d\n",ListWithFuncs1[i].name, k.IntPart,k.FloatPart);
	}

	for (int i = 0; i < TEST2_SIZE; i++) {
		k = ListWithFuncs2[i].myfunc(a1, b1);
		printf("%s: %d.%d\n", ListWithFuncs2[i].name, k.IntPart, k.FloatPart);
	}

	printf("Write ur string:\n");
	scanf("%s",&str);

	k = FixParse(str);
	printf("Parse: %d.%d\n", k.IntPart, k.FloatPart);

	test_str = FixFormat(k);
	printf("Format: %s\n", str);

	k = FixRead(INPUT_FILE);
	printf("Read: %d.%d\n", k.IntPart, k.FloatPart);
	
	if (FixWrite(k, OUTPUT_FILE)) {
		printf("Writing done!");
	}
	else {
		printf("Error while writing in file");
	}

	return 0;
}