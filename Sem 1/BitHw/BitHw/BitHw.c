#include <stdio.h>
#include <math.h>
#include <locale.h>
#pragma warning(disable:4996)
#define type (sizeof(integer_t))

//typedef unsigned char integer_t;
//typedef unsigned short integer_t;
typedef unsigned long integer_t;
typedef unsigned long Max_int;
//typedef unsigned int integer_t;
//Должны меняться только значащие пары

integer_t Process(integer_t x) {
	char rest = 1, k = 0;
	integer_t res = 0, z, t, y = 1;
	for (int i = 0; i < type * 8; i++) {
		if (x & 1 << i) {
			rest = i;
		}
			
	}
	
	t = 1 << (rest + (rest-1) % 2 - 1);
	for(int i =0;i<rest/2+1;i++) {
		res += t*((x&y)>>k);
		k++;
		t = t << 1;
		y = y << 1;
		res += t * ((x & y) >> k);
		k++;
		y = y << 1;
		t = t >> 3;
	}

	return res;
}

void PrintResult(Max_int res, char length_int) {
	char s[type*8];
	printf("%*lu = ", length_int, res);
	printf("%#0*X = ", (type*2)+2, res);
	for (int i = 0; i < type * 8; i++) {
		s[i] = res % 2;
		res /= 2;
	}
	for (int i = type * 8 - 1; i >= 0; i--) {
		printf("%d", s[i]);
	}
	printf("\n");
}
char Max_length() {
	char length = 0;
	integer_t x = (2 << 32) - 1;
	while (x) {
		length++;
		x /= 10;
	}
	return length;
}
int main()
{
	setlocale(LC_CTYPE, "Russian");
	integer_t x = 1, res;
	Max_int y;
	char MaxLengthInt;
	while (x) {
		printf("Введите число : ");
		scanf("%lu", &y);
		x = y;
		res = Process(x);
		MaxLengthInt = Max_length();
		printf("Вы ввели  : ");
		PrintResult(y, MaxLengthInt);
		printf("Результат : ");
		y = res;
		PrintResult(y, MaxLengthInt);
	}

	return 0;
}
