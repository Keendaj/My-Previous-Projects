#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define Array_Length 21
#define Word_Length 60
#define Number_Op 4
typedef int binary_op_t(int a, int b);



typedef struct oper {
	 char words[Word_Length];
	binary_op_t* func;
	int s0;
}my_oper;

int Accumulate(int const* array, int length, int s0, binary_op_t *op) {
	int s = s0;
	for (int i = 0; i < length; i++) {
		s = op(s,array[i]);
	}




	return s;
}

int Random(int a, int b) {
	double s = rand();
	s /= RAND_MAX + 1;
	s *= b - a;
	s += a;
	return s;
}

int binary_sum(int a,int b) {
	return a+b;
}
int binary_max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
int binary_neg(int s,int x) {
	if (x < 0) {
		return s + 1;
	}
	return s;
}
int binary_bin(int s, int x) {
	s = (s << 1) + x;
	return s;
}
void Fill(int a[]) {
	for (int i = 0; i < 21;i++) {
		a[i] = Random(-1,2);
	}
}

void Print(int a[]) {
	for (int i = 0; i < 21; i++) {
		printf("%d, ", a[i]);
	}
	printf("\n");
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	int res, a[Array_Length];
	my_oper Ops[4] = {
		{
			"Сумма всех чисел:",
			binary_sum,
			0
		},
		{
			"Максимальное число:",
			binary_max,
			-20
		},
		{
			"Количество отрицательных чисел:",
			binary_neg,
			0
		},
		{
			"Число в десятичной записи:",
			binary_bin,
			0
		}

	};
	Fill(a);
	Print(a);
	for (int i = 0; i < Number_Op; i++) {
		res = Accumulate(a, Array_Length, Ops[i].s0, Ops[i].func);
		printf("%s %d\n", Ops[i].words, res);
	}
	return 0;
}