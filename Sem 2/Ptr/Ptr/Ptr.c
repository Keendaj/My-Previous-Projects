#include <stdio.h>
#include <stdlib.h>
#define size 4

void first() {
	int x = 1, * ptrx = &x;
	double y = 1.1, * ptry = &y;

	printf("%d, %d\n", x, sizeof(x));
	printf("%lf, %d\n", y, sizeof(y));
	printf("%p, %d\n", ptrx, sizeof(ptrx));
	printf("%p, %d\n", ptry, sizeof(ptry));

	*ptrx = 2;
	*ptry = 2.2;

	printf("%d, %d\n", x, sizeof(x));
	printf("%lf, %d\n", y, sizeof(y));
	printf("%p, %d\n", ptrx, sizeof(ptrx));
	printf("%p, %d\n", ptry, sizeof(ptry));

}

int* array_sum(int* a, int* b, int sizea) {
	int sizet = sizea * sizeof(*a);
	int* c = malloc(sizea * sizeof(*a));
	for (int i = 0; i < sizea; i++) {
		c[i] = a[i] + b[i];
	}


	return c;
}

void printArray(int* arr, int sizea) {
	for (int i = 0; i < sizea; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void second() {
	int* ptr, * nptr, res = 0;
	int a[size] = { 1, 2, 3, 4 };
	int b[size] = { 4, 3, 2, 1 };
	printArray(a, size);
	printArray(b, size);
	ptr = array_sum(a, b, size);
	printArray(ptr, size);
	nptr = realloc(ptr, (size + 1) * sizeof(*ptr));
	if (nptr != ptr) {
		free(ptr);
	}//На stackoverflow говорят, что реаллок сам чистит прошлый указатель, если у нового другое место
	for (int i = 0; i < size; i++) {
		res += nptr[i];
	}
	
	nptr[size] = res;
	printArray(nptr, size + 1);
	

}

int Add(int a, int b) {
	return a+b;
}

int Sub(int a, int b) {
	return a-b;
}
int Add_ptr(int *a, int *b) {
	int* c;
	c = *a;
	*a = *b;
	*b = c;
	return *a + *b;
}

int Sub_ptr(int *a, int *b) {
	int* c;
	c = *a;
	*a = *b;
	*b = c;
	return *a - *b;
}


void third() {
	int a = 3, b = 1, c;
	int (*f_ptr)(int a, int b) = Add,(*f2_ptr)(int *a, int *b);
	c = f_ptr(a, b);
	printf("%d + %d = %d\n",a,b,c);
	f_ptr = Sub;
	c = f_ptr(a, b);
	printf("%d - %d = %d\n", a, b, c);
	f2_ptr = Sub_ptr;
	c = f2_ptr(&a, &b);
	printf("%d - %d = %d\n", a, b, c);
	a = 3; 
	b = 1;
	f2_ptr = Add_ptr;
	c = f2_ptr(&a, &b);
	printf("%d + %d = %d\n", a, b, c);
}

int main() {
	second();
	return 0;
}