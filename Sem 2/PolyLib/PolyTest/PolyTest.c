#include "..//PolyLib//PolyLib.h"
#pragma warning(disable:4996)
#define output "1.txt"
#define input "2.txt"
#define str "10x^4 - 2x^3 - 5x^2 + 7"

int main() {
	int arr1[6] = {1, 3 ,-4 ,5 ,2, 3 };
	poly_t poly1 = PolyFrom(6, arr1);
	char* string = PolyFormat(poly1);
	printf("%s\n", string);
	int arr2[5] = { 1, 0, -1, 1000, -2};
	poly_t poly2 = PolyFrom(5, arr2);
	string = PolyFormat(poly2);
	printf("%s\n", string);
	poly_t poly3 = PolyRead(input);
	PolyWrite(output, poly3);
	poly3 = PolyParse(str,24);
	string = PolyFormat(poly3);
	printf("%s\n", string);
	poly3 = PolySub(poly1,poly2);
	string = PolyFormat(poly3);
	printf("%s\n", string);
	poly3 = PolyAdd(poly1, poly2);
	string = PolyFormat(poly3);
	printf("%s\n", string);
	poly3 = PolyMul(poly1, poly2);
	string = PolyFormat(poly3);
	printf("%s\n", string);
	poly3 = PolyMulInt(poly1, 3);
	string = PolyFormat(poly3);
	printf("%s\n", string);
	int result = PolyEvaluate(poly1, 8.32);
	printf("%d\n", result);
	result = PolyElement(poly1, 2);
	printf("%d\n", result);
	return 0;
}