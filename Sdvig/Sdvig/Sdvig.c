#include <stdio.h>
#include <locale.h>
#define N 9
#pragma warning(disable:4996)



void Shift1(int arr[], int size) {
	int x;
	x = arr[0];
	for (int i = 0; i < size-1; i++) {
		arr[i] = arr[i + 1];
		
	}
	arr[size - 1] = x;
}

void Shift_ver1(int arr[], int size, int delta) {
	for (int i = 0; i < delta; i++) {
		Shift1(arr, size);
	}
}

void Fill(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
}

void PrintArr(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void Reverse(int arr[], int left, int right) {
	int x;
	right--;
	for (int i = left; i <(right+1+left)/2; i++) {
		x = arr[i];
		arr[i] = arr[right+left - i];
		arr[right+left - i] = x;
	}
}
void Shift_ver2(int arr[], int size, int delta) {
	Reverse(arr, 0, delta);
	Reverse(arr, delta, size);
	Reverse(arr, 0, size);
}

void ShiftLoop(int arr[], int size, int delta, int i0) {
	int x, i = i0;
	x = arr[i];
	while (1)
	{
		if (i + delta >= size) {
			arr[i] = x;
			return;
		}
		arr[i] = arr[i + delta];
		i += delta;
	}
}

void Shift_ver3(int arr[], int size,int delta, int gcd) {
	for (int i = 0; i < gcd; i++) {
		ShiftLoop(arr, size, delta, i);
	}
}

int Gcd(int a, int b) {
	int res, x;
	if (a < b) {
		x = a;
		a = b;
		b = x;
	}
	for (int i = 1; i <= a; i++) {
		if (a % i == 0 && b % i == 0) {
			res = i;
		}
	}

	return res;
}

int main() {
	int arr[N], delta, x;
	setlocale(LC_CTYPE, "Russian");
	printf("Введите сдвиг:");
	scanf("%d", &delta);
	Fill(arr, N);
	printf("Способ 1:\n");
	PrintArr(arr, N);
	Shift_ver1(arr, N, delta);
	PrintArr(arr, N);
	printf("Способ 2:\n");
	Fill(arr, N);
	PrintArr(arr, N);
	Shift_ver2(arr, N, delta);
	PrintArr(arr,N);
	printf("Способ 3:\n");
	Fill(arr, N);
	PrintArr(arr, N);
	x = Gcd(delta, N);
	Shift_ver3(arr, N, delta, x);
	PrintArr(arr, N);


	return 0;
}