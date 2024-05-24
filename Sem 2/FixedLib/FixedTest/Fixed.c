#include "..\FixedLib\FixedLib.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST1_SIZE 6
#define TEST2_SIZE 4
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#pragma warning(disable:4996)


typedef struct
{
	fixed_t(*myfunc)(fixed_t a);
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
	test1 ListWithFuncs1[TEST1_SIZE] = { {FixedNegate, "Negate"}, {FixedReciprocal, "Reciprocal"}, {FixedAbs,"Abs"},{FixedRound,"Round"},{FixedCeil,"Ceil"},{FixedFloor,"Floor"} };
	test2 ListWithFuncs2[TEST2_SIZE] = { {FixedAdd, "Add"}, {FixedSub, "Sub"}, {FixedMul,"Mul"},{FixedDiv,"Div"} };
	double a = 20.35, b = 14.5;
	int c = 10.5;
	char str[20];
	char* test_str;

	fixed_t a1 = FixedFromDouble(a);
	fixed_t b1 = FixedFromDouble(b);
	fixed_t c1 = FixedFromInt(c);
	fixed_t k;
	int new_c = FixedAsInt(c1);
	double new_a = FixedAsDouble(a1);

	for (int i = 0; i < TEST1_SIZE; i++) {
		k = ListWithFuncs1[i].myfunc(a1);
		printf("%s: %d.%d\n", ListWithFuncs1[i].name, k.IntPart, k.FloatPart);
	}

	for (int i = 0; i < TEST2_SIZE; i++) {
		k = ListWithFuncs2[i].myfunc(a1, b1);
		printf("%s: %d.%d\n", ListWithFuncs2[i].name, k.IntPart, k.FloatPart);
	}

	printf("Write ur string:\n");
	scanf("%s", &str);

	k = FixedParse(str);
	printf("Parse: %d.%d\n", k.IntPart, k.FloatPart);

	test_str = FixedFormat(k);
	printf("Format: %s\n", str);

	k = FixedRead(INPUT_FILE);
	printf("Read: %d.%d\n", k.IntPart, k.FloatPart);

	if (FixedWrite(k, OUTPUT_FILE)) {
		printf("Writing done!");
	}
	else {
		printf("Error while writing in file");
	}

	return 0;
}