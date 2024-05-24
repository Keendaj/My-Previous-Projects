#include<stdio.h>
#define MAX_LEN 10
#pragma warning (disable : 4996)

int Fill(int num, int length, int res[], int cc) {
	int true_length = 0;
	for (int i = 0; i < length; i++) {
		res[i] = num % cc;
		num = num / cc;
		if (num == 0 && true_length == 0){
			true_length = i + 1;
		}
	}

	return true_length;
}

int Add(int const a[], int const b[], int c[], int length, int cc) {
	int res, next_res = 0, true_length = 0;
	for (int i = 0; i < length; i++) {
		res = a[i] + b[i] + next_res;
		next_res = res / cc;
		res = res % cc;
		c[i] = res;
	}
	for (int i = length-1; i >= 0; i--) {
		if (c[i] && true_length == 0) {
			true_length = i + 1;
			break;
		}
	}

	return true_length;

}
void Print(int res[],int length, int aligment) {
	for (int i = aligment-length; i >= 0; i--) {
		printf(" ");
	}
	for (int i = length - 1; i >= 0; i--) {
		printf("%d",res[i]);
	}
	printf("\n");
}
int Collect(int a[], int length, int cc) {
	int res = 0, var = 1;
	for (int i = length - 1; i >= 0; i--) {
		if (var && a[i]) {
			var = 0;
		}
		else if (var) {
			continue;
		}
		res = res * cc + a[i];
	}
	
	return res;
}
int main() {
	int a1, a2[MAX_LEN], b1, b2[MAX_LEN], c1, c2[MAX_LEN], alength, blength, clength, cc;
	printf("Enter cc: ");
	scanf("%d", &cc);
	printf("Enter first number: ");
	scanf("%d", &a1);
	alength = Fill(a1, MAX_LEN, a2,cc);
	printf("Enter second number: ");
	scanf("%d", &b1);
	blength = Fill(b1, MAX_LEN,b2,cc);
	clength = Add(a2, b2, c2, MAX_LEN, cc);
	printf("Your answer:\n");
	Print(a2, alength,clength);
	printf("+");
	printf("\n");
	Print(b2, blength, clength);
	for (int i = clength; i >= 0; i--) {
		printf("-");
	}
	printf("\n");
	Print(c2, clength, clength);
	
	return 0;

}