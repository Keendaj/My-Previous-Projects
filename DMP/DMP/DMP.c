#include <stdio.h>
#include <malloc.h>
#include "DMP.h"
#define N 9


void FillInt(int *a,int length) {
	int k = 600;
	for (int i = 0; i < length; i++) {
		a[i] = k;
		k += 2;
	}
}

void FillDouble(double *b, int length) {
	double k = 600;
	for (int i = 0; i < length; i++) {
		b[i] = k;
		k += 2;
	}
}

void PrintInt(int const *a, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d",a[i]);
	}
}

void PrintDouble(double const* a, int length) {
	for (int i = 0; i < length; i++) {
		printf("%lf", a[i]);
	}
}

void MemoryDump(void const *ptr, int size) {
	unsigned char *a = (unsigned const char*)ptr;
	int z, f = 1, y = size, ind = 0;
	if(size%16){
		f = 0;
	}
	for (int k = 0; k <= size / 16 - f; k++) {
		printf("%p: ", a);
		z = (k + 1) * 16;
		if (y < 16) {
			z = k*16 + y;
			ind = 1;
		}
		
		for (int i = k*16; i < z; i++) {
			printf("%02x ", *(a+i));
		}
		if (ind) {
			for (int i = 0; i < 3 * (16-y); i++) {
				printf(" ");
			}
		}
		for (int i = k * 16; i < z; i++) {
			int d = *(a + i);
			if (isprint(*(a + i))) {
				printf("%c", *(a + i));
			}
			else {
				printf(".");
			}
		}
		y -= 16;
		printf("\n");
	}
}


int main() {
	int* a;
	double* b;
	a = malloc(sizeof(int)*N);
	b = malloc(sizeof(double) * N);
	FillInt(a, N);
	FillDouble(b, N);
	printf("Int: \n");
	MemoryDump(a, sizeof(*a)*N);
	printf("Double: \n");
	MemoryDump(b, sizeof(*b) * N);




	return 0;
}